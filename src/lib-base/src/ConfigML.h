#ifndef CONFIGML_H
#define CONFIGML_H

#include "ConfigBase.h"
#include "OptionsNumeric.h"
#include <3rdParty/stdfwd.hh>

enum class RDEType;
enum class RFEType;
enum class DTWDistType;

class ConfigML : public ConfigBase
{
    public:
        ConfigML();
        virtual ~ConfigML();

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        RDEType GetRDEType() const;
        RFEType GetRFEType() const;
        DTWDistType GetDistType() const;
        float GetPCAQuality() const;
        EnjoLib::Str GetRelDebDir() const;

        bool ML_INV_BARS = false;       static const char * OPT_ML_INV_BARS;
        bool ML_FIND_HORI = false;      static const char * OPT_ML_FIND_HORI;
        bool ML_REM_ERRATIC = false;    static const char * OPT_ML_REM_ERRATIC;
        bool ML_USE_RELEASE = false;    static const char * OPT_ML_USE_RELEASE;
        bool ML_REUSE_PCA  = false;

        long int PCA_QUAL  = 95;
        long int PCA_NUM = 0;
        long int LEN_TECHS = 15;
        long int LEN_TECHS_MIN = 15;
        long int LEN_TECHS_MAX = 15;
        long int RFE_TYPE  = 0;
        long int RDE_TYPE  = 0;
        long int DIST_TYPE = 0;
        long int VERBOSITY = 0;
        long int ML_NUM_CVS = 3;

    protected:

        EnjoLib::Str GetFileNameProt() const override;

    private:
};

#endif // CONFIGML_H
