#include "StatsMedianSplit.h"

#include "Buffer.h"
#include "BufferType.h"
#include "IDataProvider.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"

#include "URTWrap.h"

#include <Util/VecOp.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/VecD.hpp>
#include <Util/CoutBuf.hpp>
#include <Statistical/Matrix.hpp>
#include <Statistical/Statistical.hpp>
#include <Statistical/Formatters.hpp>
#include <Math/GeneralMath.hpp>

#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>

#include <future>
#include <thread>

using namespace std;
using namespace EnjoLib;

StatsMedianSplit::StatsMedianSplit(bool multiThreaded)
: m_multiThreaded(multiThreaded)
{}
StatsMedianSplit::~StatsMedianSplit(){}


StatsMedianSplit::Results StatsMedianSplit::CalcResults(const IDataProvider & dat, int numRanges) const
{
    const URTWrap urtWrap;
    const Statistical stat;
    const Buffer bufStat = dat.GetBuf(BUF_STATION); /// TODO: Bottleneck
    const EnjoLib::VecF & dataStat = bufStat.GetData();

    const VecD & vecWZeros = dataStat.Data();
    const VecD & vecNoZeros = stat.RemoveLeadingZeroes(vecWZeros);
    const Results res = CalcResults(vecWZeros, numRanges);

    urtWrap.Show(vecNoZeros.Data());
    return res;
}

void StatsMedianSplit::Stats(const IDataProvider & dat, int numRanges) const
{
    ELO
    if (not gcfgMan.cfgTF2->STATS_SUMMARY)
    {
        LOG << "StatsMedianSplit::Stats disabled via cfgTF2->STATS_SUMMARY\n";
        return;
    }

    const Results & res = CalcResults(dat, numRanges);
    const EnjoLib::Str & rep = Report(dat.GetSymbolPeriodId(), res);
    LOG << rep << Nl;
    LOG << "StatsMedianSplit::Stats size = " << dat.Len() << Nl;
}

void StatsMedianSplit::Stats(const EnjoLib::Str & idd, const EnjoLib::VecD & dat, int numRanges) const
{
    const Results & res = CalcResults(dat, numRanges);
    const EnjoLib::Str & rep = Report(idd, res);
    ELO
    LOG << rep << Nl;
    LOG << "StatsMedianSplit::Stats size = " << dat.Len() << Nl;
}

StatsMedianSplit::Results StatsMedianSplit::CalcResults(const EnjoLib::VecD & vecWZeros, int numRanges) const
{
    const URTWrap urtWrap;
    const Statistical stat;
    const VecD & vecNoZeros = stat.RemoveLeadingZeroes(vecWZeros);

    const vector<vector<EnjoLib::FP>> & dataSplit = VecOp().Split(vecNoZeros.Data(), numRanges);

    std::future<double> fut;
    if (m_multiThreaded)
    {
        fut = std::async(std::launch::async, [&]{ return urtWrap.GetStatistic(vecNoZeros.Data()); });
    }

    Results res;
    for (unsigned i = 0; i < dataSplit.size(); ++i)
    {
        const VecD & vec = dataSplit.at(i);
        const double mea = stat.Mean(vec);
        const double dev = stat.StandardDeviation(vec);
        const double urt = urtWrap.GetStatistic(vec.Data());
        const int num = vec.size();

        res.means.push_back(mea);
        res.devs.push_back(dev);
        res.urts.push_back(urt);
        res.nums.push_back(num);

        res.num += num;
        //LOGL << vec.Print() << Nl;
    }
    res.mean = stat.SpreadMinMax(res.means);
    res.dev  = stat.SpreadMinMax2Avg(res.devs);

    if (m_multiThreaded)
    {
        res.urt  = fut.get();
    }
    else
    {
        res.urt  = urtWrap.GetStatistic(vecNoZeros.Data());
    }



    //urtWrap.Show(vecNoZeros.Data());
    return res;
}

EnjoLib::Str StatsMedianSplit::Report(const EnjoLib::Str & idd, const Results & res) const
{
    const int prec = 3;
    const Formatters fmt(prec);
    const Statistical stat;
    const GeneralMath gmat;
    const EnjoLib::Str & lineSep = CharManipulations().GetLineSeparator(14 * 4);
    EnjoLib::Osstream oss;
    oss << '\n' << idd << " - Stats\n";
    oss << "  Mean\t\t  StdDev\t  URT\t\tSamples\n" << lineSep;
    for (unsigned i = 0; i < res.means.size(); ++i)
    {
        const double medi = res.means.at(i);
        const double devi = res.devs.at(i);
        const double urti = res.urts.at(i);
        const int nums = res.nums.at(i);
        oss << fmt.FormatVar(medi) << "\t\t";
        oss << fmt.FormatVar(devi) << "\t\t";
        oss << fmt.FormatVar(urti) << "\t\t";
        oss << nums << Nl;
    }
    oss << lineSep;
    oss << fmt.FormatVar(res.mean) << "\t\t";
    oss << fmt.FormatVar(gmat.Percent(res.dev), false, 1) << "%" << "\t\t";
    oss << fmt.FormatVar(res.urt) << "\t\t";
    oss << res.num << Nl;
    return oss.str();
}
