#ifndef CONFIG_SYM_H
#define CONFIG_SYM_H

#include "ConfigBase.h"
class StrategyType;
enum class DataSrcType;
#include "DataDates.h"

#include <Util/Str.hpp>

class ConfigSym : public ConfigBase
{
    public:
        ConfigSym();
        virtual ~ConfigSym();

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        //void SetStandardVals();
        bool ShiftRange(int shift);
        EnjoLib::Str GetDateFromToStr(bool lineBreak = true) const;
        EnjoLib::Str GetDataSrcDir() const;
        EnjoLib::Str GetDataBinDir() const;
        EnjoLib::Str GetDataExt() const;

        StrategyType GetStrat() const;
        DataSrcType GetDataSrc() const;
        long int GetStratInt() const { return strat; }
        long int GetDataSrcInt() const { return DATA_SOURCE; }

        void SetStrat(long int parStrat);
        void SetStrat(const StrategyType & parStrat);
        void SetDataSrc(long int parDataSrc);
        void SetDataSrc(const DataSrcType & parStrat);


        DataDates dates;
        long int percentBars = 100;
        long int barNum = 0;
        EnjoLib::Str symbol, period;

    protected:
        EnjoLib::Str GetFileNameProt() const override;
        EnjoLib::Str GetDataDir(const EnjoLib::Str & baseDir) const;
    private:
        bool ShiftRangeUpdate(int change, long int * year, long int * month);

        long int strat;
        long int DATA_SOURCE = 0;
};

#endif // CONFIG_SYM_H
