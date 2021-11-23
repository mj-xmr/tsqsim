#ifndef CONFIGTF2_H
#define CONFIGTF2_H

#include "ConfigBase.h"
#include "DataDates.h"
#include "OptionsNumeric.h"

enum class SimulatorType;

class ConfigTF2 : public ConfigBase
{
    public:
        ConfigTF2();
        virtual ~ConfigTF2(){}

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        bool ClearBlacklist() const;
        int GetNumThreads() const;
        SimulatorType GetSimType() const;
        float GetRandomBarsPercent() const;
        bool UsesNetwork() const;

        long int PLOTS = 0;
        long int THREADS = 0;
        long int RANDOM_BARS_PERCENT = 0;
        long int RANDOM_BARS_SEED = 0;
        long int MT_SIM_TYPE = 0;       static const char * OPT_SIM_TYPE;
        long int EXPERIM_INT_1 = 0;
        long int EXPERIM_INT_2 = 0;
        bool MT_SIM_UPDATE_TECH = false;
        bool SIM_USE_TICKS = false;
        bool TRAIN = false;             static const char * OPT_TRAIN;
        bool FULL_DATA = false;
        bool CUSTOM_DATE = false;
        bool PYTHON_SERVER = true;
        bool BLACKLIST = true;
        bool OPTIM_COSTLY = false;
        bool CORREL_CALC = false;
        bool CORREL_USE = false;
        bool CORREL_ADAPT = false;
        bool EXPERIMENTAL = false;
        bool POTENTIAL_PROFIT = false;
        bool RANDOM_BARS = false;
        bool FILTER_PRICE = false;      static const char * OPT_FILTER_PRICE;
        bool NETWORKED = false;
        bool NETWORKED_CV = false;
        bool PLOT_COUMPOUNDED = false;
        bool SINGLE_THREADED_ALL = false;
        bool STATS_SUMMARY = false;
        bool CAP_CORREL_ADJ = false;
        //bool NO_AT_ACCESS = false;
        long int SPREAD_MUL_FILTER = 0;

        DataDates dates;

    protected:
        EnjoLib::Str GetFileNameProt() const override;
    private:
};

#endif // CONFIGTF2_H
