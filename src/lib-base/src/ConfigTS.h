#ifndef CONFIGTS_H
#define CONFIGTS_H

#include "ConfigBase.h"
#include <Util/Str.hpp>

class ConfigTS : public ConfigBase
{
    public:
        ConfigTS();
        virtual ~ConfigTS();

        void RegisterAndReadBools (EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts  (EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs  (EnjoLib::Istream & ifs) override;

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        static const char * DEFAULT_SCRIPT_FILE_NAME;

        EnjoLib::Str m_scriptPathTxt;
        bool crashOnRecoverableErrors = false;
        bool PLOT_SERIES = true;

    protected:
        EnjoLib::Str GetFileNameProt() const override;

    private:
};

#endif // CONFIGTS_H
