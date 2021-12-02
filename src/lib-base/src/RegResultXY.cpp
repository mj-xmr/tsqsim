#include "RegResultXY.h"
#include <Math/MaxMinFind.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/PimplCopier.hpp>
#include <Util/PimplDeleter.hpp>

#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

struct RegResultXY::Impl
{
    Impl()
    {
        m_data.push_back(&regLine);
        m_data.push_back(&regOver);
        m_data.push_back(&regUndr);
        m_data.push_back(&regOverBody);
        m_data.push_back(&regUndrBody);
        m_data.push_back(&regOverUnderAvg);
    }
    template <class T>
    void EraseAllButLastTpl(std::vector<T> * data)
    {
        if (data->empty())
            return;
        data->erase(data->begin(), data->end() - 1);
    }
    
    void EraseAllButLast()
    {
        for (auto & data : m_data)
        {
            EraseAllButLastTpl(data);
        }
            
        EraseAllButLastTpl(&zzz);
    }
    void Reserve(int memSize)
    {
        for (auto & data : m_data)
        {
            data->reserve(memSize);
        }
    }

    void Shrink2Fit()
    {
        for (auto & data : m_data)
        {
            data->shrink_to_fit();
        }
    }
    
    std::vector<XY> regLine;
    std::vector<XY> regOver;
    std::vector<XY> regUndr;
    std::vector<XY> regOverBody;
    std::vector<XY> regUndrBody;
    std::vector<XY> regOverUnderAvg;
    std::vector<XYDir> zzz;
    
    std::vector<std::vector<XY> * > m_data;
};

PIMPL_COPIER(RegResultXY)
PIMPL_DELETER(RegResultXY)
    
RegResultXY::~RegResultXY(){}
RegResultXY::RegResultXY(const RegressionPars & pars)
: m_impl(new Impl())
, regPar(pars)
{

}

double RegResultXY::GetDelta() const
{
    if (not IsValid())
        return 0;

    if (regRes.coeffs.size() <= 2)
    {
        const double delta = EnjoLib::GeneralMath().Fabs(GetImpl().regLine.back().y - GetImpl().regLine.front().y);
        return delta;
    }
    EnjoLib::MaxMinFind<double> mmfa;

    for (unsigned i = 0; i < GetImpl().regLine.size(); ++i)
        mmfa.UpdateMaxMin(GetImpl().regLine.at(i).y, i);
    const int extrIdx = regRes.IsBullish() ? mmfa.GetMinIdx() : mmfa.GetMaxIdx();
    double sum = 0;
    for (unsigned i = extrIdx + 1; i < GetImpl().regLine.size(); ++i)
    {
        const double yPrev = GetImpl().regLine.at(i-1).y;
        const double yCurr = GetImpl().regLine.at(i).y;
        sum += EnjoLib::GeneralMath().Fabs(yPrev - yCurr);
    }
    return sum; // Promotes round
}

double RegResultXY::GetDelta2RMS() const
{
    if (not IsValid())
        return 0;
    const double delta = GetDelta();
    const double delta2RMS = delta / regRes.rms;

    return delta2RMS;
}

double RegResultXY::GetLen2RMS() const
{
    if (not IsValid())
        return 0;
        
    const GeneralMath gmat;

    const double len2RMS = gmat.Log(GetImpl().regLine.size()) / regRes.rms / 1000.0;

    return len2RMS;
}

bool RegResultXY::IsValid() const
{
    if (regRes.rms == 0)
        return false;
    return not regRes.coeffs.empty();
    //return not regLine.empty() and not regOver.empty() and not regUndr.empty();
}

float RegResultXY::GetSumZZ() const
{
    if (not IsValid())
        return 0;

    float sum = 0;
    for (int i = 1; i < int(GetImpl().zzz.size()); ++i)
    {
        const XYDir & prev = GetImpl().zzz.at(i-1);
        const XYDir & curr = GetImpl().zzz.at(i);
        const float diff = EnjoLib::GeneralMath().Fabs(curr.y - prev.y);
        sum += diff;
        //cout << "diff = " << diff << ", i1 = " << prev.x << ", i2 = " << curr.x << endl;
    }
    //cout << "sum = " << sum << endl;
    return sum;
}

void RegResultXY::EraseAllButLast()
{
    if (not IsValid())
        return;

    GetImplRW().EraseAllButLast();
}

XY RegResultXY::FindXYInRegResultXY(const EnjoLib::Array<XY> & vxy, int sti)
{
    for (const XY & xy : vxy)
    {
        if (xy.x == sti)
        {
            return xy;
        }
    }
    return XY();
}

void RegResultXY::Reserve(int memSize)
{
    GetImplRW().Reserve(memSize);
}

void RegResultXY::Shrink2Fit()
{
    GetImplRW().Shrink2Fit();
}

Array<XY> RegResultXY::regLine() const { return GetImpl().regLine; }
Array<XY> RegResultXY::regOver() const { return GetImpl().regOver; }
Array<XY> RegResultXY::regUndr() const { return GetImpl().regUndr; }
Array<XY> RegResultXY::regOverBody() const { return GetImpl().regOverBody; }
Array<XY> RegResultXY::regUndrBody() const { return GetImpl().regUndrBody; }
Array<XY> RegResultXY::regOverUnderAvg() const { return GetImpl().regOverUnderAvg; }
const stdfwd::vector<XYDir> & RegResultXY::zzz() const { return GetImpl().zzz; }

const float & RegResultXY::regLineBackY() const { return GetImpl().regLine.back().y; }
const float & RegResultXY::regOverBackY() const { return GetImpl().regOver.back().y; }
const float & RegResultXY::regUndrBackY() const { return GetImpl().regUndr.back().y; }
const float & RegResultXY::regOverBodyBackY() const { return GetImpl().regOverBody.back().y; }
const float & RegResultXY::regUndrBodyBackY() const { return GetImpl().regUndrBody.back().y; }
const float & RegResultXY::regOverUnderAvgBackY() const { return GetImpl().regOverUnderAvg.back().y; }
const XYDir & RegResultXY::zzzBack() const { return GetImpl().zzz.back(); }

const XY & RegResultXY::regLineBack() const { return GetImpl().regLine.back(); }
const XY & RegResultXY::regOverBack() const { return GetImpl().regOver.back(); }
const XY & RegResultXY::regUndrBack() const { return GetImpl().regUndr.back(); }
const XY & RegResultXY::regOverBodyBack() const { return GetImpl().regOverBody.back(); }
const XY & RegResultXY::regUndrBodyBack() const { return GetImpl().regUndrBody.back(); }
const XY & RegResultXY::regOverUnderAvgBack() const { return GetImpl().regOverUnderAvg.back(); }

stdfwd::vector<XY> & RegResultXY::regLine() { return GetImplRW().regLine; }
stdfwd::vector<XY> & RegResultXY::regOver() { return GetImplRW().regOver; }
stdfwd::vector<XY> & RegResultXY::regUndr() { return GetImplRW().regUndr; }
stdfwd::vector<XY> & RegResultXY::regOverBody() { return GetImplRW().regOverBody; }
stdfwd::vector<XY> & RegResultXY::regUndrBody() { return GetImplRW().regUndrBody; }
stdfwd::vector<XY> & RegResultXY::regOverUnderAvg() { return GetImplRW().regOverUnderAvg; }
stdfwd::vector<XYDir> & RegResultXY::zzz() { return GetImplRW().zzz; }

size_t RegResultXY::size() const
{
    return GetImpl().regLine.size();
}
