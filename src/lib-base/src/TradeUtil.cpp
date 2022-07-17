#include "TradeUtil.h"
#include "ConfigDirs.h"
#include "IDataProvider.h"
#include "Candle.h"
#include "ISymbol.h"
#include "DayOfWeekCandle.h"
#include "ConfigSym.h"
#include "ConfigMan.h"

#include <Util/CharManipulations.hpp>
#include <Util/CharManipulationsTpl.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/FileUtils.hpp>
#include <Util/ToolsMixed.hpp>
#include <Util/VecF.hpp>
#include <Util/CoutBuf.hpp>
#include <Ios/Ifstream.hpp>
#include <Math/GeneralMath.hpp>
#include <Math/MaxMinFind.hpp>
#include <Statistical/Matrix.hpp>
#include <Template/Array.hpp>
#include <EnjoLibBoost/Filesystem.hpp>

#include <STD/VectorCpp.hpp>
#include <STD/Set.hpp>
#include <STD/String.hpp>
#include <STD/Iomanip.hpp>
#include <STD/Ostream.hpp>
#include <ctime>

using namespace std;
using namespace EnjoLib;

const EnjoLib::Str TradeUtil::SYMBOL_TEST_PREFIX = "Test-";

TradeUtil::TradeUtil(){}
TradeUtil::~TradeUtil(){}

TradeUtil::DateTimeTok::DateTimeTok(VecStr date, VecStr time)
: date(date), time(time)
{

}

EnjoLib::Str TradeUtil::Date2Str(DateInt date, bool dateOnly) const
{
    EnjoLib::Osstream oss;
    oss << date;
    string str = oss.str().str();
    for (int i = str.size()-1; i >= 4; --i)
    {
        if (i == 8)
        {
            str = str.insert(i, "  ");
            //str = str.insert(i, spaces);
            continue;
        }
        if (i == 10)
        {
            str = str.insert(i, ":");
            continue;
        }
        if (i % 2 == 0)
        {
            str = str.insert(i, "-");
        }

    }
    if (dateOnly)
        str = str.erase(str.size()-8);
    else
        str = str.erase(str.size()-3);
    return str;
}

EnjoLib::Str TradeUtil::Date2DateRawStr(DateInt date) const
{
    EnjoLib::Osstream oss;
    oss << date;
    const string dateStr = oss.str().str().substr(0, 8);
    return dateStr;
}

EnjoLib::Str TradeUtil::Date2TimeRawStr(DateInt date) const
{
    EnjoLib::Osstream oss;
    oss << date;
    const string hour = oss.str().str().substr(8);
    return hour;
}

EnjoLib::Str TradeUtil::Date2StrUnderscores(DateInt date, bool dateOnly) const
{
    EnjoLib::Str strDate = Date2Str(date, dateOnly);
    strDate = EnjoLib::CharManipulations().Replace(strDate, " ", "_");
    strDate = EnjoLib::CharManipulations().Replace(strDate, "-", "_");
    strDate = EnjoLib::CharManipulations().Replace(strDate, ":", "_");
    return strDate;
}

EnjoLib::Str TradeUtil::LabelLineToUnderscoresWXid(const EnjoLib::Str & labelLine) const
{
    const VecStr & tokens = Tokenizer().Tokenize(labelLine, '|');
    if (tokens.size() < 4)
    {
        throw EnjoLib::ExceptInvalidArg("TradeUtil::LabelLineToUnderscoresWXid() Incorrect format: " + labelLine.str());
    }
    const char del = '_';
    Str date = tokens.at(2);
    DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(date);
    EnjoLib::Str dateUnderscores = Date2StrUnderscores(YYYYMMDDhhmmss);
    EnjoLib::Str ret = tokens.at(0) + del + tokens.at(1) + del + dateUnderscores;
    //EURUSD|h1|20160322130000|20160405080000
    // to :
    //AUDUSD_h2_2016_09_13__10_00

    return ret;

}

DateInt TradeUtil::DateUSA2DateInt(const EnjoLib::Str & dateStr) const
{
    const DateTimeTok dt = TokenizeDateTime(dateStr);
    const string joined = dt.date.at(2).str() + dt.date.at(0).str() + dt.date.at(1).str() + dt.time.at(0).str() + dt.time.at(1).str() + dt.time.at(2).str();
    const DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(joined);
    return YYYYMMDDhhmmss;
}

DateInt TradeUtil::DateISOdot2DateInt(const EnjoLib::Str & dateStr) const
{
    const DateTimeTok dt = TokenizeDateTime(dateStr);
    const string joined = dt.date.at(0).str() + dt.date.at(1).str() + dt.date.at(2).str() + dt.time.at(0).str() + dt.time.at(1).str() + dt.time.at(2).str();
    const DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(joined);
    return YYYYMMDDhhmmss;
}

DateInt TradeUtil::Timestamp2DateInt(const EnjoLib::Str & timestampStr) const
{
    time_t tsp = CharManipulationsTpl().ToNumber<time_t>(timestampStr);
    const std::tm* t = std::gmtime(&tsp);
    Osstream oss;
    oss.OStr() << std::put_time(t, "%Y%m%d%H%M%S");
    const Str & str = oss.str();
    const DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(str);
    return YYYYMMDDhhmmss;
}

TradeUtil::DateTimeTok TradeUtil::TokenizeDateTime(const EnjoLib::Str & dateStr) const
{
    VecStr dateTime = Tokenizer().Tokenize(dateStr, ' ');
    Str date = dateTime.at(0);
    Str time = dateTime.at(1);
    date = CharManipulations().Replace(date, "-", ".");
    VecStr dateTok = Tokenizer().Tokenize(date, '.');
    VecStr timeTok = Tokenizer().Tokenize(time, ':');
    if (timeTok.size() < 3)
        timeTok.push_back("00"); // Add missing seconds
    return DateTimeTok(dateTok, timeTok);
}

DateInt TradeUtil::DateISO2DateInt(int year, int month, int day) const
{
    EnjoLib::Osstream oss;
    oss << year;
    if (month < 10)
        oss << "0";
    oss << month;
    if (day < 10)
        oss << "0";
    oss << day;
    oss << "000000";
    DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(oss.str());
    return YYYYMMDDhhmmss;
}

DateInt TradeUtil::SigIdUnderscore2DateInt(const EnjoLib::Str & sigIdUnderscore) const
{
    EnjoLib::Str joined = JoinDateUnderscore(sigIdUnderscore, 2);
    DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(joined);
    return YYYYMMDDhhmmss;
}

DateInt TradeUtil::DateUnderscore2DateInt(const EnjoLib::Str & dateStrUnderscore) const
{
    EnjoLib::Str joined = JoinDateUnderscore(dateStrUnderscore, 0);
    DateInt YYYYMMDDhhmmss = CharManipulationsTpl().ToNumber<DateInt>(joined);
    return YYYYMMDDhhmmss;
}

DateInt TradeUtil::DateZeroMinute(DateInt date) const
{
    return DateZeroNumSuffix(date, 4);
}

DateInt TradeUtil::DateZeroHour(DateInt date) const
{
    return DateZeroNumSuffix(date, 6);
}

DateInt TradeUtil::DateZeroNumSuffix(DateInt date, int numZeros) const
{
    EnjoLib::Osstream oss;
    oss << date;
    string str = oss.str().str();
    str = str.erase(str.size() - numZeros);
    const string addedZeroes(numZeros, '0');
    str += addedZeroes;
    const DateInt zeroMinute = CharManipulationsTpl().ToNumber<DateInt>(str);
    return zeroMinute;
}

EnjoLib::Str TradeUtil::JoinDateUnderscore(const EnjoLib::Str & dateStrUnderscore, int startingIndex) const
{
    VecStr tok = Tokenizer().Tokenize(dateStrUnderscore, '_');
    string joined;
    for (unsigned i = startingIndex; i < tok.size(); ++i)
        joined += tok[i].str();

    joined += "00";
    return joined;
}

#include "SymAliases.h"
// Removes TEST-
EnjoLib::Str TradeUtil::CutSymbolTestingPrefix(const EnjoLib::Str & symbolName) const
{
    CharManipulations cm;


    //ret = cm.Replace(ret, SYMBOL_TEST_PREFIX, ""); // breaks tests
    //ret = cm.Replace(ret, cm.ToUpper(SYMBOL_TEST_PREFIX), "");
    if (cm.StartsWith(symbolName, SYMBOL_TEST_PREFIX) || cm.StartsWith(symbolName, cm.ToUpper(SYMBOL_TEST_PREFIX)))
    {
        EnjoLib::Str ret = symbolName;
        ret.strRW().erase(ret.strRef().begin(), ret.strRef().begin() + SYMBOL_TEST_PREFIX.length());
        static SymAliases symAliases;
        const EnjoLib::Str & alias = symAliases.GetAlias(ret);
        return alias;
    }
    return symbolName;
}

EnjoLib::Pair<int, int> TradeUtil::GetYearMonthMax(const EnjoLib::Str & symbolName) const
{
    EnjoLib::Pair<int, int> err(2018, 12);
    MaxMinFind<int> maxMonth, maxYear;
    const EnjoLib::Str dirBase = gcfgMan.cfgSym->GetDataBinDir() + symbolName + "/";
    if (not FileUtils().DirExists(dirBase))
    {
        return err;
    }
    const VecStr & files = EnjoLib::Filesystem().ListDir(dirBase);
    if (files.empty())
    {
        return err;
    }
    for (const Str & file : files)
    {
        LOGL << dirBase << "/" << file << Endl;
        if (file.str().find("-2") == string::npos) { // Expecting a year
            continue;
        }
        const auto tok =      Tokenizer().Tokenize(file, '-');
        const auto tokMonth = Tokenizer().Tokenize(tok.at(2), '.');
        const int year = CharManipulations().ToInt(tok.at(1));
        const int mont = CharManipulations().ToInt(tokMonth.at(0));
        if (maxYear.UpdateMax(year))
        {
            // Reset month for each new year
            maxMonth = MaxMinFind<int>();
        }
        maxMonth.UpdateMax(mont);
    }
    const int year = maxYear .GetMax();
    const int mont = maxMonth.GetMax();
    LOGL << symbolName << ": Year/month max = " << year << "." << mont << Endl;
    return EnjoLib::Pair<int, int>(year, mont);

}

bool TradeUtil::IsBlacklisted(const std::set<EnjoLib::Str> & blacklist, const EnjoLib::Str & sym, const EnjoLib::Str & per) const
{
    const EnjoLib::Str symPerId = sym + '-' + per;
    return blacklist.count(symPerId) || blacklist.count(sym);
}

VecStr TradeUtil::GetAllSymbolsFromTxtDir() const
{
    VecStr symbolsListed;
    for (const EnjoLib::Str & file : GetAllSymbolsFromTxtDirRaw())
    {
        CharManipulations cms;
        //if (not cms.EndsWith(file, ".txt.gz")) // FX
        if (not cms.EndsWith(file, ".gz")) // Monero uses csv
        {
            continue;
        }
        const Str symbol = Tokenizer().Tokenize(file, '.').at(0);
        symbolsListed.push_back(symbol.str());
    }
    return symbolsListed;
}

VecStr TradeUtil::GetAllSymbolsFromTxtDirRaw() const
{
    gcfgMan.Read();
    const EnjoLib::Filesystem fss;
    const EnjoLib::CharManipulations cmp;
    const EnjoLib::Str dataDir = gcfgMan.cfgSym->GetDataSrcDir();
    const EnjoLib::Str extension = gcfgMan.cfgSym->GetDataExt() + ".gz";
    LOGL << "Data, ext = " << dataDir << ", " << extension << Nl;
    const VecStr & symbols = fss.ListDir(dataDir, extension);
    return symbols;
}

VecStr TradeUtil::GetAllSymbolsFromCorrelsFile(float minCorrel) const
{
    Ifstream ifile(ConfigDirs().DIR_DATA + ConfigDirs().FILE_CORREL_LIST);
    return GetAllSymbolsFromCorrelsFile(minCorrel, ifile);
}
std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> TradeUtil::GetPairsSymbolsFromCorrelsFile(float minCorrel) const
{
    Ifstream ifile(ConfigDirs().DIR_DATA + ConfigDirs().FILE_CORREL_LIST);
    return GetPairsSymbolsFromCorrelsFile(minCorrel, ifile);
}
VecStr TradeUtil::GetAllSymbolsFromStatsFile(float minSharpe) const
{
    Ifstream ifile(ConfigDirs().DIR_DATA + ConfigDirs().FILE_CRYPTO_STATS.str());
    return GetAllSymbolsFromStatsFile(minSharpe, ifile);
}
std::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> TradeUtil::GetPairsSymbolsLeverageFromStatsFile(float minSharpe, float maxDD) const
{
    Ifstream ifile(ConfigDirs().DIR_DATA + ConfigDirs().FILE_CRYPTO_STATS.str());
    return GetPairsSymbolsLeverageFromStatsFile(minSharpe, maxDD, ifile);
}
std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> TradeUtil::GetPairsSymbolsFromStatsFile(float minSharpe) const
{
    Ifstream ifile(ConfigDirs().DIR_DATA + ConfigDirs().FILE_CRYPTO_STATS.str());
    return GetPairsSymbolsFromStatsFile(minSharpe, ifile);
}

VecStr TradeUtil::GetAllSymbolsFromCorrelsFile(float minCorrel, EnjoLib::Istream & is) const
{
    std::set<EnjoLib::Str> indivSymbols;
    Tokenizer tok;
    for (const Str & line : tok.GetLines(is))
    {
        const auto symSymCorr = ParseSymbolsCorrelLine(line);
        const float correl = Get<2>(symSymCorr);
        if (GMat().Fabs(correl) < minCorrel) // Filter out poor correlations
            continue;
        const EnjoLib::Str sym1 = Get<0>(symSymCorr);
        const EnjoLib::Str sym2 = Get<1>(symSymCorr);

        indivSymbols.insert(sym1);
        indivSymbols.insert(sym2);
    }
    VecStr ret;
    for (EnjoLib::Str sym : indivSymbols)
        ret.push_back(sym);
    return ret;
}

EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, int> TradeUtil::ParseSymbolsCorrelLine(const Str & line) const
{
    Tokenizer tok;
    CharManipulations cms;
    // format: GBPJPY-GBPUSD-h1 = 0.900402
    const VecStr mainTok = tok.Tokenize(line, '=');
    const Str left  = cms.Trim(mainTok.at(0));
    const Str right = cms.Trim(mainTok.at(1));

    const VecStr symbolsAndPeriod = tok.Tokenize(left, '-');
    const VecStr correlAndConvergence = tok.Tokenize(right, ',');

    const Str sym1 = symbolsAndPeriod.at(0);
    const Str sym2 = symbolsAndPeriod.at(1);

    const float correl = cms.ToDouble(correlAndConvergence.at(0));
    const int converged = cms.ToInt(correlAndConvergence.at(1));

    EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, int> ret;
    Get<0>(ret) = sym1;
    Get<1>(ret) = sym2;
    Get<2>(ret) = correl;
    Get<3>(ret) = converged;
    return ret;
}

std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> TradeUtil::GetPairsSymbolsFromCorrelsFile(float minCorrel, EnjoLib::Istream & is) const
{
    std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> ret;
    Tokenizer tok;
    for (const Str & line : tok.GetLines(is))
    {
        const auto symSymCorr = ParseSymbolsCorrelLine(line);
        const float correl = Get<2>(symSymCorr);
        if (correl < minCorrel) // Filter out poor correlations
            continue;
        const EnjoLib::Str sym1 = Get<0>(symSymCorr);
        const EnjoLib::Str sym2 = Get<1>(symSymCorr);

        ret.push_back(EnjoLib::MakePair(sym1, sym2));
        ret.push_back(EnjoLib::MakePair(sym2, sym1));
    }

    return ret;
}

VecStr TradeUtil::GetAllSymbolsFromStatsFile(float minSharpe, EnjoLib::Istream & is) const
{
    std::set<EnjoLib::Str> indivSymbols;
    Tokenizer tok;
    for (const EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str> & symPair : GetPairsSymbolsFromStatsFile(minSharpe, is))
    {
        indivSymbols.insert(symPair.first);
        indivSymbols.insert(symPair.second);
    }
    VecStr ret;
    for (EnjoLib::Str sym : indivSymbols)
        ret.push_back(sym);
    return ret;
}

std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> TradeUtil::GetPairsSymbolsFromStatsFile(float minSharpe, EnjoLib::Istream & is) const
{
    std::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> ret;
    Tokenizer tok;
    for (const Str & line : tok.GetLines(is))
    {
        const auto symSymCorr = ParseSymbolsStatsLine(line);
        const float sharpe = Get<2>(symSymCorr);
        if (sharpe < minSharpe) // Filter out poor sharpes
            continue;
        const EnjoLib::Str sym1 = Get<0>(symSymCorr);
        const EnjoLib::Str sym2 = Get<1>(symSymCorr);

        ret.push_back(EnjoLib::MakePair(sym1, sym2));
    }
    return ret;
}

std::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> TradeUtil::GetPairsSymbolsLeverageFromStatsFile(float minSharpe, float maxMaxDD, EnjoLib::Istream & is) const
{
    std::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> ret;
    Tokenizer tok;
    for (const Str & line : tok.GetLines(is))
    {
        const auto symSymCorr = ParseSymbolsStatsLine(line);
        const float sharpe = Get<2>(symSymCorr);
        const float maxDD  = Get<3>(symSymCorr);
        if (sharpe < minSharpe) // Filter out poor correlations
            continue;
        const EnjoLib::Str sym1 = Get<0>(symSymCorr);
        const EnjoLib::Str sym2 = Get<1>(symSymCorr);

        const float leverage = EnjoLib::GeneralMath().Fabs(maxMaxDD / maxDD);

        EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float> ele;
        Get<0>(ele) = sym1;
        Get<1>(ele) = sym2;
        Get<2>(ele) = leverage;

        ret.push_back(ele);
    }
    return ret;
}

EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, float, float> TradeUtil::ParseSymbolsStatsLine(const EnjoLib::Str & line) const
{
    Tokenizer tok;
    CharManipulations cms;
    // cols:   Symbol-SymCor-h1 sharpe  maxDD
    // format: WTIUSD-BCOUSD-h1 0.32324 -0.08
    const VecStr mainTok = tok.Tokenize(line, ' ');
    const Str left  = cms.Trim(mainTok.at(0));
    const VecStr symbolsAndPeriod = tok.Tokenize(left, '-');
    const Str sym1 = symbolsAndPeriod.at(0);
    const Str sym2 = symbolsAndPeriod.at(1);


    const Str sharpeStr = cms.Trim(mainTok.at(1));
    const Str maxDDStr  = cms.Trim(mainTok.at(2));
    const Str levarStr  = cms.Trim(mainTok.at(3));
    const float sharpe = cms.ToDouble(sharpeStr);
    const float maxDD  = cms.ToDouble(maxDDStr);
    const float levar  = cms.ToDouble(levarStr);

    EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, float, float> ret;
    Get<0>(ret) = sym1;
    Get<1>(ret) = sym2;
    Get<2>(ret) = sharpe;
    Get<3>(ret) = maxDD;
    Get<4>(ret) = levar;

    return ret;
}

EnjoLib::Str TradeUtil::MinutesToPeriodName(int minutes) const
{
    switch (minutes)
    {
    case 1:
        return "m1";
    case 5:
        return "m5";
    case 15:
        return "m15";
    case 30:
        return "m30";
    case 60:
        return "h1";
    case 120:
        return "h2";
    case 240:
        return "h4";
    case 480:
        return "h8";
    case 720:
        return "h12";
    case 1440:
        return "d";
    }
    throw EnjoLib::ExceptInvalidArg("Unsupported period = " + EnjoLib::CharManipulations().ToStr(minutes));
}

/// Don't allow opening trades on Friday after 7p.m.
bool TradeUtil::IsOpeningTradesAllowed(const ISymbol & sym, const Candle & can) const
{
    if (sym.IsMetaTrader())
    {
        if (can.GetHour() < 19)
        {
            return true;
        }
        DayOfWeekCandle dow(can);
        if (dow.GetDay() == EnjoLib::DayOfWeek::Friday)
        {
            return false;
        }
    }
    return true;
}

EnjoLib::Str TradeUtil::GetSymSymCorrPerNameId(const IDataProvider & per, const IDataProvider * perCorrel) const
{
    EnjoLib::Osstream oss;
    oss << per.GetSymbolName();
    if (perCorrel)
    {
        oss << '-' << perCorrel->GetSymbolName();
    }
    oss << '-' << per.GetName();
    return oss.str();
}

EnjoLib::Str TradeUtil::GetSymbolPeriodCandleIdUnified(const IDataProvider & per, DateInt date) const
{
    return GetSymbolPeriodCandleIdUnified(per.GetSymbolPeriodId('_'), date);
}

EnjoLib::Str TradeUtil::GetSymbolPeriodCandleIdUnified(const EnjoLib::Str & symPerdiodUnderscored, DateInt date) const
{
    return symPerdiodUnderscored + '_' + TradeUtil().Date2StrUnderscores(date);
}


EnjoLib::Str TradeUtil::GetOutputDir(const IDataProvider & per) const
{
    return GetOutputDir(per.GetSymbolPeriodId());
}

EnjoLib::Str TradeUtil::GetOutputDir(const EnjoLib::Str & fullIdOfSymbolsPeriods) const
{
    return GetOutputDirAccum() + '/' + fullIdOfSymbolsPeriods + '/';
}

EnjoLib::Str TradeUtil::GetOutputDirAccum() const
{
    return ConfigDirs().DIR_OUT + '/';
}

EnjoLib::VecF  TradeUtil::GetAverage(const EnjoLib::Array<EnjoLib::VecF > & vdata) const
{
    Matrix mat;
    VecF ret;
    for (unsigned i = 0; i < vdata.size(); ++i)
    {
        const EnjoLib::VecF & data = vdata.at(i);
        mat.Add(data);
    }
    mat.TMe();
    for (const auto & row : mat)
    {
        const double avg = row.Mean();
        ret.push_back(avg);
    }
    return ret;
}

EnjoLib::Str TradeUtil::GetLineFXfromSeries(DateInt dateTime, const EnjoLib::Str & txnumbStr) const
{
    const Str & date = Date2DateRawStr(dateTime);
    const Str & time = Date2TimeRawStr(dateTime);

    Osstream ostr;
    ostr << "MONERO,"  << date  << ","  << time;
    const Str txNumbStrLine = "," + txnumbStr;
    for (int i = 0; i < 4; ++i)
    {
        ostr << txNumbStrLine;
    }
    ostr << ",0";

    return ostr.str();
}
