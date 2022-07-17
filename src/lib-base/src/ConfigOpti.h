#ifndef CONFIGOPTI_H
#define CONFIGOPTI_H

#include "ConfigBase.h"
#include <3rdParty/stdfwd.hh>

class IPeriod;
enum class OptiType;
enum class OptiMethod;
enum class OptiGoalType;

class ConfigOpti : public ConfigBase
{
    public:
        ConfigOpti();
        virtual ~ConfigOpti();

        void FromOptsNumeric(const OptionsNumeric & optsNum) override;

        void RegisterAndReadBools(EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts(EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats(EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs(EnjoLib::Istream & ifs) override;

        int   GetOPTI_CROSS_VALID_BARS_OPTI(const IPeriod & per) const;
        float GetOPTI_CROSS_VALID_BARS_XVAL(const IPeriod & per) const;
        EnjoLib::Str GetRelDebDir() const;
        //bool IsUseOpti() const;
        bool IsSearchFloatingPoint() const;
        bool IsSearchGrid() const;
        bool IsSearchRandom() const;
        bool IsXValid() const;
        bool IsOptimizing() const;
        bool IsOperationType(const OptiType & operType) const;
        OptiType GetOperationType() const;
        OptiMethod GetMethod() const;
        OptiGoalType GetGoalType() const;

        void SetOptimizer(const OptiType & optiType);
        void SetOptimizerMethod(const OptiMethod & optiMethod);
        void SetOptimizerGoal(const OptiGoalType & optiGoal);

        long int OPTIMIZER = 0; // 0 = No, default; 1 = Optimize; 2 = Use selected solution
        long int OPTIMIZER_METHOD = 0; // 0 = Grid, default; 1 = MonteCarlo; 2 = Nelder
        long int OPTIMIZER_GOAL = 0;

        bool OPTI_VERBOSE = true;
        bool OPTI_RANDOM_EARLY_STOP = false;
        bool OPTI_USE_RELEASE = true;
        bool OPTI_GLOBAL = false;
        bool OPTI_LAST = false;
        bool OPTI_SERVER_DENSE = false;
        bool OPTI_XVAL_EXTENDABLE = false;

        long int OPTI_CROSS_VALID_BARS_OPTI_H1 = 2000;
        long int OPTI_CROSS_VALID_BARS_XVAL = 20;
        long int OPTI_RANDOM_SAMPLES_NUM = 100;
        long int OPTI_RANDOM_MIN_DIFF_PROMILE = 10; // For early stop's % std dev changes


    protected:

        EnjoLib::Str GetFileNameProt() const override;

    private:
};

#endif // CONFIGOPTI_H
