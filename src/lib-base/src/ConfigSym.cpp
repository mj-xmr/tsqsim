#include "ConfigSym.h"

#include <Util/Except.hpp>

#include <Ios/Osstream.hpp>
#include "Consts.h"
#include "TradeUtil.h"
#include "StrategyType.h"
#include "DataSrcType.h"
////#include "ConfigGlob.h"
#include "ConfigDirs.h"

#include <Util/CharManipulations.hpp>
#include <Util/Except.hpp>
#include <Util/Pair.hpp>

using namespace std;
using namespace EnjoLib;

ConfigSym::ConfigSym()
{
}
ConfigSym::~ConfigSym(){}

EnjoLib::Str ConfigSym::GetFileNameProt() const
{
    return "configSymbol.txt";
}

void ConfigSym::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

void ConfigSym::RegisterAndReadBools(EnjoLib::Istream & f)
{
}
void ConfigSym::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, percentBars, 100);
    RegisterAndReadInt (f, barNum, 0);
    RegisterAndReadInt (f, dates.yearStart, 2015);
    RegisterAndReadInt (f, dates.yearEnd, 2015);
    RegisterAndReadInt (f, dates.monthStart, 1);
    RegisterAndReadInt (f, dates.monthEnd, 2);
    RegisterAndReadInt (f, strat, 0);
    RegisterAndReadInt (f, DATA_SOURCE, 1); /// TODO: express with a converted enum
}
void ConfigSym::RegisterAndReadFloats(EnjoLib::Istream & f)
{
}
void ConfigSym::RegisterAndReadStrs(EnjoLib::Istream & f)
{
    RegisterAndReadStr(f, symbol, "TX-TS");
    RegisterAndReadStr(f, period, "h8");
}

void ConfigSym::UpdateFromOther(const ConfigSym & cfgSymCmdLine)
{
    dates.UpdateIfNot0(cfgSymCmdLine.dates);
    if (cfgSymCmdLine.symbol.size()) symbol = cfgSymCmdLine.symbol;
    if (cfgSymCmdLine.period.size()) period = cfgSymCmdLine.period;
}

/*
void ConfigSym::SetStandardVals()
{
    yearStart = YEAR_MIN;
    yearEnd = YEAR_MAX;
    monthStart = MONTH_MIN;
    monthEnd = MONTH_MAX;
    strat = 0;
    //symbol = "AUDUSD";
    //period = "h4";
}
*/

StrategyType ConfigSym::GetStrat() const
{
    return strat;
}
DataSrcType ConfigSym::GetDataSrc() const
{
    return static_cast<DataSrcType>(DATA_SOURCE);
}
void ConfigSym::SetStrat(long int parStrat)
{
    strat = parStrat;
}

void ConfigSym::SetStrat(const StrategyType & parStrat)
{
    SetStrat(static_cast<long int>(parStrat.GetType()));
}

void ConfigSym::SetDataSrc(long int parStrat)
{
    DATA_SOURCE = parStrat;
}

void ConfigSym::SetDataSrc(const DataSrcType & parStrat)
{
    SetDataSrc(static_cast<long int>(parStrat));
}


bool ConfigSym::ShiftRange(int shift)
{
    const int diffYears = dates.yearEnd - dates.yearStart;
    const int diffMonths = dates.monthEnd - dates.monthStart;
    int diff = diffMonths + diffYears * 12 - 1;
    if (diff <= 0)
        diff = 1;
    const int change = diff * shift; // include sign

    ConfigSym backup = *this;
    if (not ShiftRangeUpdate(change, &dates.yearStart, &dates.monthStart))
    {
        return false;
    }
    if (not ShiftRangeUpdate(change, &dates.yearEnd,   &dates.monthEnd))
    {
        return false;
    }


    const Pair<int, int> yearMonthMax = TradeUtil().GetYearMonthMax(symbol);
    const int yearMax = yearMonthMax.first;
    const int monthMax = yearMonthMax.second;
    if ((dates.yearStart < YEAR_MIN) ||
        ((dates.yearEnd >   yearMax) || (dates.yearEnd == yearMax && dates.monthEnd > monthMax)) )
    {
        *this = backup;
        return false;
    }
    return true;
}

bool ConfigSym::ShiftRangeUpdate(int change, long int * year, long int * month)
{
    long int & y = *year;
    long int & m = *month;
    m += change;
    while(m < 1)
    {
        m += 12;
        y --;
    }
    while (m > 12)
    {
        m -= 12;
        y ++;
    }

    return true;
}

EnjoLib::Str ConfigSym::GetDateFromToStr(bool lineBreak) const
{
    CharManipulations cma;
    EnjoLib::Osstream oss;
    oss << dates.yearStart << "." << cma.MakeLeadingZeroes(dates.monthStart, 2);
    oss << (lineBreak ? "\n" : " - " );
    oss << dates.yearEnd   << "." << cma.MakeLeadingZeroes(dates.monthEnd, 2) << Nl;
    return oss.str();
}

EnjoLib::Str ConfigSym::GetDataBinDir() const
{
    const ConfigDirs cfg;
    const EnjoLib::Str & ret = cfg.DIR_DATA_BIN;
    return GetDataDir(ret);
}

EnjoLib::Str ConfigSym::GetDataSrcDir() const
{
    const ConfigDirs cfg;
    const EnjoLib::Str & ret = cfg.DIR_DATA_TXT;
    return GetDataDir(ret);
}

EnjoLib::Str ConfigSym::GetDataDir(const EnjoLib::Str & baseDir) const
{
    switch (GetDataSrc())
    {
    case DataSrcType::FOREX_TESTER:
        return baseDir + "fxt/";
    case DataSrcType::MONERO:
        return baseDir + "xmr/";
    case DataSrcType::GENERATED:
        return baseDir + "generated/";
    }
    throw ExceptNotImpl("ConfigSym::GetDataDir()" +baseDir);
}

EnjoLib::Str ConfigSym::GetDataExt() const
{
    switch (GetDataSrc())
    {
    case DataSrcType::FOREX_TESTER:
        return ".txt";
    case DataSrcType::MONERO:
        return ".csv";
    case DataSrcType::GENERATED:
        return ".txt";
    }
    throw ExceptNotImpl("ConfigSym::GetDataExt()");
}
