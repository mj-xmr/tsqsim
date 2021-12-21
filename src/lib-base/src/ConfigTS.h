#ifndef CONFIGTS_H
#define CONFIGTS_H

#include "ConfigBase.h"
#include <Util/Str.hpp>

enum class PredictorType;

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
        
        PredictorType GetPredType() const;
        void SetPredType(const PredictorType & type);

        static const char * DEFAULT_SCRIPT_FILE_NAME;

        EnjoLib::Str m_scriptPathTxt;
        bool crashOnRecoverableErrors = false;
        bool PLOT_SERIES = true;
        bool MT_REPORT = false;
        bool MT_XFORM = false;
        
        long int PRED_TYPE = 0;

    protected:
        EnjoLib::Str GetFileNameProt() const override;

    private:
};

#endif // CONFIGTS_H
