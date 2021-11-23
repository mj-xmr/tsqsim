#ifndef CONFIGTF_H
#define CONFIGTF_H

#include "ConfigBase.h"
#include "OptionsNumeric.h"

class ConfigTF : public ConfigBase
{
    public:
        ConfigTF();
        virtual ~ConfigTF();

        void RegisterAndReadBools (EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts  (EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs  (EnjoLib::Istream & ifs) override;
        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        static const char * OPT_INDIVIDUAL_PERIOD;
        static const char * OPT_INDIVIDUAL_SYMBOL;
        static const char * OPT_INDIVIDUAL_STRAT;
        static const char * OPT_PLOT_TYPE;
        static const char * OPT_REPEAT;
        static const char * OPT_SIMUL_MULTITHREAD;

        long int INDIVIDUAL_PERIOD = 0; // 0 = All; 1 = Single;
        long int INDIVIDUAL_SYMBOL = 0; // 0 = All; 1 = Single; 2 = Labels
        long int INDIVIDUAL_STRAT  = 0; // 0 = All; 1 = Single; 2 = Predefined; 3 = Dummy; 4 = CacheFiller
        long int PLOT_TYPE = 0; // 0 = No
        bool REPEAT = false;
        bool SIMUL_MULTITHREAD = true;

    protected:
        EnjoLib::Str GetFileNameProt() const override;
    private:
};

#endif // CONFIGTF_H
