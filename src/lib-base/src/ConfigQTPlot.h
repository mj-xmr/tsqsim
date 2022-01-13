#ifndef CONFIGQTPLOT_H
#define CONFIGQTPLOT_H

#include "ConfigBase.h"
#include <3rdParty/stdfwd.hh>

class ConfigQTPlot : public ConfigBase
{
    public:
        ConfigQTPlot();
        virtual ~ConfigQTPlot();

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        bool CANDLES = true;
        bool SIGNAL_TRADE = true;
        bool SIGNAL_SPECIAL = true;
        bool PROFIT = true;
        bool SIMUL = true;
        bool SR = true;
        bool SR_GROUPS = true;
        bool TPS = true;
        bool TECHS = true;
        bool SL = true;
        bool MA = true;
        bool STD_DEV = true;
        bool ZIG_ZAG = true;
        bool ZIG_ZAG_INDEXES = true;
        bool DAY_WEEK = true;
        bool BET = false;
        bool DARK = false;
        bool WEEKEND_DATA = true;

    protected:
        EnjoLib::Str GetFileNameProt() const override;
    private:
};

#endif // CONFIGQTPLOT_H
