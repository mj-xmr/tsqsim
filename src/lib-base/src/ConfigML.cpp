#include "ConfigML.h"
#include <Util/Str.hpp>

const char * ConfigML::OPT_ML_USE_RELEASE = "ml-release";
const char * ConfigML::OPT_ML_FIND_HORI   = "ml-find-hori";
const char * ConfigML::OPT_ML_INV_BARS    = "ml-inv-bars";
const char * ConfigML::OPT_ML_REM_ERRATIC = "ml-rem-erratic";



ConfigML::ConfigML(){}
ConfigML::~ConfigML(){}

void ConfigML::FromOptsNumeric(const OptionsNumeric & optsNum)
{
    UpdateVarIfConfigured(optsNum, ML_USE_RELEASE,  OPT_ML_USE_RELEASE);
    UpdateVarIfConfigured(optsNum, ML_FIND_HORI,    OPT_ML_FIND_HORI);
    UpdateVarIfConfigured(optsNum, ML_INV_BARS,     OPT_ML_INV_BARS);
    UpdateVarIfConfigured(optsNum, ML_REM_ERRATIC,  OPT_ML_REM_ERRATIC);
}

void ConfigML::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool (f, ML_INV_BARS, false,         "ML_INV_BARS");
    RegisterAndReadBool (f, ML_FIND_HORI,     false,    "ML_FIND_HORI");
    RegisterAndReadBool (f, ML_USE_RELEASE,   false,    "ML_USE_RELEASE");
    RegisterAndReadBool (f, ML_REM_ERRATIC,   false,    "ML_REM_ERRATIC");
    RegisterAndReadBool (f, ML_REUSE_PCA,   false   ,   "ML_REUSE_PCA");
}

void ConfigML::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, PCA_QUAL,  95);
    RegisterAndReadInt (f, LEN_TECHS, 15);
    RegisterAndReadInt (f, LEN_TECHS_MIN, 15);
    RegisterAndReadInt (f, LEN_TECHS_MAX, 15);

    RegisterAndReadInt (f, RFE_TYPE,  0);
    RegisterAndReadInt (f, RDE_TYPE,  0);
    RegisterAndReadInt (f, DIST_TYPE, 0);
    RegisterAndReadInt (f, VERBOSITY, 0);

    RegisterAndReadInt (f, ML_NUM_CVS, 3);

    RegisterAndReadInt (f, PCA_NUM, 0);
}

void ConfigML::RegisterAndReadFloats(EnjoLib::Istream & f)
{

}

void ConfigML::RegisterAndReadStrs(EnjoLib::Istream & f)
{
}

RFEType ConfigML::GetRFEType() const
{
    return RFEType(RFE_TYPE);
}

RDEType ConfigML::GetRDEType() const
{
    return RDEType(RDE_TYPE);
}

DTWDistType ConfigML::GetDistType() const
{
    return DTWDistType(DIST_TYPE);
}

float ConfigML::GetPCAQuality() const
{
    return PCA_QUAL / 100.0;
}

EnjoLib::Str ConfigML::GetRelDebDir() const
{
    return GetRelDebDirBase(ML_USE_RELEASE);
}

EnjoLib::Str ConfigML::GetFileNameProt() const
{
    return "configML.txt";
}
