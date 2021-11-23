#ifndef CONFIGQT_H
#define CONFIGQT_H

#include "ConfigBase.h"
#include "Util/Str.hpp"
#include <3rdParty/stdfwd.hh>

class ConfigQT : public ConfigBase
{
    public:
        ConfigQT();
        virtual ~ConfigQT();

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        EnjoLib::Str dateTime;
        long int buf1 = 0;
        long int buf2 = 0;
        long int buf3 = 0;
        long int bufRainbow = 0;
        bool BIG_SCREEN = true;
        bool DIRECTION = true;
        bool PLOT_SIG_LAB = false;
        bool USE_CACHE = true;

    protected:
        EnjoLib::Str GetFileNameProt() const override;
    private:
};

#endif // CONFIGQT_H
