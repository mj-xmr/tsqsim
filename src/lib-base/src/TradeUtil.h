#ifndef TRADEUTIL_H
#define TRADEUTIL_H

#include "types.h"
#include "Direction.h"
#include <Util/VecFwd.hpp>
#include <Util/VecStr.hpp>
#include <Util/Pair.hpp>
#include <Util/Tuple.hpp>
#include <Ios/Istream.hpp>
#include <Template/ArrayFwd.hpp>

class ISymbol;
class IStrategy;
class IPeriod;
class IDataProvider;
class BufferType;
class Candle;
class TradeUtil
{
    public:
        TradeUtil();
        virtual ~TradeUtil();
        EnjoLib::Str Date2Str(DateInt date, bool dateOnly = false) const;
        EnjoLib::Str Date2DateRawStr(DateInt date) const;
        EnjoLib::Str Date2TimeRawStr(DateInt date) const;
        EnjoLib::Str Date2StrUnderscores(DateInt date, bool dateOnly = false) const;
        DateInt DateUSA2DateInt(const EnjoLib::Str & dateStr) const;
        DateInt DateISOdot2DateInt(const EnjoLib::Str & dateStr) const;
        DateInt Timestamp2DateInt(const EnjoLib::Str & dateStr) const;
        DateInt DateISO2DateInt(int year, int month, int day) const;
        DateInt DateUnderscore2DateInt(const EnjoLib::Str & dateStrUnderscore) const;
        DateInt SigIdUnderscore2DateInt(const EnjoLib::Str & sigIdUnderscore) const;
        DateInt DateZeroMinute(DateInt date) const;
        DateInt DateZeroHour(DateInt date) const;
        DateInt DateZeroNumSuffix(DateInt date, int numZeros) const;
        EnjoLib::Pair<int, int> GetYearMonthMax(const EnjoLib::Str & symbolName) const;

        EnjoLib::Str MinutesToPeriodName(int minutes) const;

        EnjoLib::Str CutSymbolTestingPrefix(const EnjoLib::Str & symbolName) const;
        EnjoLib::Str LabelLineToUnderscoresWXid(const EnjoLib::Str & labelLine) const;

        bool IsBlacklisted(const STDFWD::set<EnjoLib::Str> & blacklist, const EnjoLib::Str & sym, const EnjoLib::Str & per) const;

        EnjoLib::VecF GetAverage(const EnjoLib::Array<EnjoLib::VecF> & vdata) const;

        VecStr GetAllSymbolsFromTxtDirRaw() const;
        VecStr GetAllSymbolsFromTxtDir() const;
        VecStr GetAllSymbolsFromCorrelsFile(float minCorrel) const;
        VecStr GetAllSymbolsFromCorrelsFile(float minCorrel, EnjoLib::Istream & is) const;
        VecStr GetAllSymbolsFromStatsFile(float minSharpe) const;
        VecStr GetAllSymbolsFromStatsFile(float minSharpe, EnjoLib::Istream & is) const;

        STDFWD::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> GetPairsSymbolsFromCorrelsFile(float minCorrel) const;
        STDFWD::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> GetPairsSymbolsFromCorrelsFile(float minCorrel, EnjoLib::Istream & is) const;
        EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, int> ParseSymbolsCorrelLine(const EnjoLib::Str & line) const;

        STDFWD::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> GetPairsSymbolsFromStatsFile(float minSharpe) const;
        STDFWD::vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> GetPairsSymbolsFromStatsFile(float minSharpe, EnjoLib::Istream & is) const;
        STDFWD::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> GetPairsSymbolsLeverageFromStatsFile(float minSharpe, float maxDD) const;
        STDFWD::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> GetPairsSymbolsLeverageFromStatsFile(float minSharpe, float maxDD, EnjoLib::Istream & is) const;
        EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float, float, float> ParseSymbolsStatsLine(const EnjoLib::Str & line) const;

        EnjoLib::Str GetSymSymCorrPerNameId(const IDataProvider & per, const IDataProvider * perCorrel = nullptr) const;
        EnjoLib::Str GetSymbolPeriodCandleIdUnified(const IDataProvider & per, DateInt date) const;
        EnjoLib::Str GetSymbolPeriodCandleIdUnified(const EnjoLib::Str & symPerdiodUnderscored, DateInt date) const;
        bool IsOpeningTradesAllowed(const ISymbol & sym, const Candle & can) const;

        EnjoLib::Str GetOutputDir(const IDataProvider & strat) const;
        EnjoLib::Str GetOutputDir(const EnjoLib::Str & fullIdOfSymbolsPeriods) const;
        EnjoLib::Str GetOutputDirAccum() const;

        EnjoLib::Str GetLineFXfromSeries(DateInt dateTime, const EnjoLib::Str & txnumbStr) const;


        const static EnjoLib::Str SYMBOL_TEST_PREFIX;

    protected:
    private:
        struct DateTimeTok
        {
            DateTimeTok(VecStr date, VecStr time);
            VecStr date;
            VecStr time;
        };
        DateTimeTok TokenizeDateTime(const EnjoLib::Str & dateStr) const;
        EnjoLib::Str JoinDateUnderscore(const EnjoLib::Str & dateStrUnderscore, int startingIndex) const;
};

#endif // TRADEUTIL_H
