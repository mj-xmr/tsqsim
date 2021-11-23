#ifndef IMODEL_H
#define IMODEL_H

#include <State.h>
#include <Statistical/Matrix.hpp>
#include <Statistical/EigenAbstract.hpp>
#include <Statistical/EigenFactoryAbstract.hpp>
#include <Util/Str.hpp>
#include <Template/CorradePointer.h>
//#include <Template/CorradePointerFwd.h>
#include <3rdParty/stdfwd.hh>
class IDataProvider;
class IPeriod;
class BufferType;
class BufferVecType;
class StrategyFactoryAbstract;
class Factories;
//class EigenAbstract;
enum class RFEType;
enum class DTWDistType;
enum class RDEType;

class IModel
{
    public:
        IModel(const IPeriod & per, const Factories & fact);
        virtual ~IModel();

        virtual int MIN_LEN() const = 0;
        virtual int MIN_DIFF_IDX() const = 0;
        virtual int LAB_WINDOW() const = 0;
        virtual int LAB_WINDOW_TECHS() const = 0;

        virtual float SPREAD_MUL_MIN_GAIN() const = 0;
        //virtual float PROC_NEGATIVE_FIRST const = 0;
        virtual float SPREAD_MUL_MAX_GAIN() const = 0;
        virtual float GetTPMul() const = 0;
        virtual float GetSLStdDevMulFixedPercent() const = 0;
        virtual EnjoLib::Str GetName() const = 0;

        virtual int GetNumCVs() const;
        virtual bool IS_INVERTED_BARS() const;
        virtual bool IsPricePercent() const;
        virtual bool IsPriceCorrected() const;
        virtual bool IsFilterByMedian() const; /// TODO: replace with proper filtering

        virtual float GetPCAQuality() const;
        virtual int GetPCANumberFeatures() const;
        virtual DTWDistType GetDisttype() const;
        virtual RFEType GetRFEtype() const;
        virtual RDEType GetRDEtype() const;

        virtual EnjoLib::Matrix GetLabelObserv(int stiCurr) const = 0;
        virtual bool IsBasicCondition(ST) const = 0;

        const IDataProvider & GetPer() const;
        const EnjoLib::EigenAbstract & GetEigen() const;

        void SetLenTechs(int lenTechs);
        int GetLenTechsOverride() const;
        //void SetNumErraticLabels2Remove(int numLabs);

    protected:
        struct Transform
        {
            Transform(){}
            double mul = 1;
            double add = 0;
        };
        void AddTech        (int sti, EnjoLib::VecD * columns, const BufferType & type) const;
        void AddTechVec     (int sti, EnjoLib::VecD * columns, const BufferVecType & type, const Transform & tr = Transform()) const;
        void AddTechVecDiffs(int sti, EnjoLib::VecD * columns, const BufferVecType & type) const;

        const IPeriod & m_per;
        const Factories & m_fact;
        Corrade::Containers::Pointer<EnjoLib::EigenAbstract> m_eigen;



    private:
        int m_lenTechsOverride = 0;
};

#endif // IMODEL_H
