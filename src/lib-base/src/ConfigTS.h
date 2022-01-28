#ifndef CONFIGTS_H
#define CONFIGTS_H

#include "ConfigBase.h"
#include <Util/Str.hpp>

enum class PredictorType;
enum class PriceType;

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

        PriceType GetPriceType() const;
        void SetPriceType(const PriceType & type);

        void UpdateFromOther(const ConfigTS & cfgTSCmdLine);


        static const char * DEFAULT_SCRIPT_FILE_NAME;
        static const char * DEFAULT_SCRIPT_FILE_NAME_R;
        static const char * DEFAULT_SCRIPT_FILE_NAME_GEN;

        EnjoLib::Str m_scriptPathTxt;
        EnjoLib::Str m_scriptPathTxtR;
        EnjoLib::Str m_scriptPathTxtGen;
        bool crashOnRecoverableErrors = false;
        bool PLOT_SERIES = true;
        bool PLOT_BASELINE = true;
        bool PLOT_PYTHON = false;
        bool PLOT_PYTHON_ACF = false;
        bool MT_REPORT = false;
        bool MT_XFORM = false;
        bool USE_VECTOR_PRED = false;

        long int PRED_TYPE = 0;
        long int PRICE_TYPE = 0;
        long int PLOT_LAGS_NUM = 30; constexpr static const char * DESCR_PLOT_LAGS_NUM = "Number of lags for ACF/PACF plot";
        long int PLOT_PERIOD_NUM = 30; constexpr static const char * DESCR_PLOT_PERIOD_NUM = "Seasonal period for seasonal decomposition plot";

    protected:
        EnjoLib::Str GetFileNameProt() const override;

    private:
};

#endif // CONFIGTS_H
