#include "RegressionPoints.h"
#include "IDataProvider.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "GnuplotIOSWrap.h"
#include "Logic.h"
#include <Math/GeneralMath.hpp>
#include <Util/VecOpThin.hpp>
#include <Template/Array.hpp>
#include <Statistical/Assertions.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

const int RegressionPoints::m_numBins = 20;

RegressionPoints::RegressionPoints()
: m_distributionIn(m_numBins)
, m_distributionOut(m_numBins)
{}
RegressionPoints::~RegressionPoints(){}

float RegressionPoints::GetPoints() const
{
    float error = 0;
    const Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & data = GetDistrib();
    for (unsigned i = 0; i < data.size(); ++i)
    {
        const double x = data.at(i).first;
        const double y = data.at(i).second;
        const double normY = GetNormalDistrib(x);
        const float errLoc = EnjoLib::GeneralMath().Fabs(y - normY);
        error += errLoc;
    }
    return error;
}

double RegressionPoints::GetNormalDistrib(double x) const
{
    const GeneralMath gmt;
    double nom = gmt.Exp(-5.5 * x*x);
    double den = gmt.Sqrt(2 * 3.14);
    return nom/den;
}

void RegressionPoints::AddPoint(const IDataProvider & period, int j, float valCurr, float diffLoMin, float diffHiMax)
{
    const GeneralMath gmt;
    const IBufferCandles & bufCan = period.GetCandles();
    const Candle & can = bufCan[j];
    float hi = can.GetHigh();
    float lo = can.GetLow();
    const float rangeHi = valCurr + diffHiMax;
    const float rangeLo = valCurr - diffLoMin;
    if (hi > rangeHi)
        hi = rangeHi;
    if (lo < rangeLo)
        lo = rangeLo;
    const float rangeDiff = rangeHi - rangeLo;
    const float binLen = rangeDiff / float(m_numBins);
    const int nbinLo = gmt.round((lo-rangeLo) / binLen);
    const int nbinHi = gmt.round((hi-rangeLo) / binLen);

    for (int i = nbinLo; i < nbinHi; ++i)
    {
        m_distributionIn.atw(i)++;
    }
    m_vValCurr.emplace_back(valCurr);
    m_vHi.emplace_back(hi);
    m_vLo.emplace_back(lo);
}

float RegressionPoints::GetAvgSpread() const
{
    if (m_vHi.empty())
        return 0;
    float sumDiff = 0;
    for (int i = 0; i < int(m_vHi.size()); ++i)
    {
        const float diff = m_vHi.at(i) - m_vLo.at(i);
        sumDiff += diff;
    }
    const float avg = sumDiff / float(m_vHi.size());
    return avg;
}

float RegressionPoints::GetMaxSpread() const
{
    if (m_vHi.empty())
        return 0;
    float maxSpread = 0;
    for (int i = 0; i < int(m_vHi.size()); ++i)
    {
        const float diff = m_vHi.at(i) - m_vLo.at(i);
        if (diff > maxSpread)
            maxSpread = diff;
    }
    return maxSpread;
}

float RegressionPoints::GetRange() const
{
    if (m_vValCurr.empty())
        return 0;
    const float start = m_vValCurr.at(0);
    for (int i = 2; i < int(m_vValCurr.size()); ++i)
    {
        const float val2 = m_vValCurr.at(i-2);
        const float val1 = m_vValCurr.at(i-1);
        const float val0 = m_vValCurr.at(i);
        bool extremeReached = not EnjoLib::Assertions::In(val2, val1, val0);
        if (extremeReached)
        {
            const float range = EnjoLib::GeneralMath().Fabs(val1 - start);
            //cout << "Val1 = " << val1 << ", start = " << start << endl;
            return range;
        }
    }
    return 0;
}

void RegressionPoints::Finish()
{
    int iMax = VecOpThin().FindMaxIdx(m_distributionIn);
    const float max = m_distributionIn.at(iMax);
    const float mul = 0.4 / max;
    for (unsigned i = 0; i < m_distributionOut.size(); ++i)
        m_distributionOut.atw(i) = m_distributionIn.at(i) * mul;
}

EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> RegressionPoints::GetDistrib() const
{
    std::vector<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> data;
    for (unsigned i = 0; i < m_distributionOut.size(); ++i)
    {
        double moved = i - (m_numBins / 2.0 - 1);
        double scaleFactor = 2.5 / m_numBins;
        EnjoLib::FP scaledX = moved * scaleFactor;
        data.push_back(EnjoLib::MakePair(scaledX, m_distributionOut.at(i)));
    }
    return data;
}

// Wykrywac wszystkie mody powyzej 0.35
float RegressionPoints::GetMedian() const
{
    const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & distrib = GetDistrib();
    double maxArg = -1;
    double maxVal = -1;
    for (int i = 0; i < int(distrib.size()); ++i)
    {
        double arg = distrib.at(i).first;
        double val = distrib.at(i).second;

        if (maxVal < 0 || val > maxVal)
        {
            maxVal = val;
            maxArg = arg;
        }
    }
    return maxArg;
}

/// TODO: Upstream ?
float RegressionPoints::GetDistribDiff(const RegressionPoints & other) const
{
    const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & distrib1 = GetDistrib();
    const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & distrib2 = other.GetDistrib();

    double sum = 0;

    for (int i = 0; i < int(distrib2.size()); ++i)
    {
        double val1 = distrib1.at(i).second;
        double val2 = distrib2.at(i).second;
        double diffAbs = EnjoLib::GeneralMath().Fabs(val1 - val2);
        sum += diffAbs;
    }
    return sum;
}

void RegressionPoints::Plot() const
{
    GnuplotPlotTerminal2d(GetDistrib());
}

