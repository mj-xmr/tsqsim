#ifndef OPTIVARTPL_H
#define OPTIVARTPL_H

#include <Util/Str.hpp>
#include <Util/VecFwd.hpp>

class IDataProvider;

class OptiVarF
{
    public:
        OptiVarF(const IDataProvider & period, const EnjoLib::Str & pvarId, bool fp, float valDefault, float valMin, float valMax, float step, bool multiplyStep = false);
        OptiVarF(const IDataProvider & period, const EnjoLib::Str & pvarId, bool fp, const EnjoLib::VecF & valDefaultMinMaxStep, bool multiplyStep = false);
        virtual ~OptiVarF();

        EnjoLib::VecF GetSpace() const;
        void StoreVariable(const IDataProvider & period) const;
        void Init();
        float GetVal() const;
        const float & GetValRef() const;
        void SetVal(float val);

        static EnjoLib::VecF GetSpaceDiscrete(float valMin, float valMax, float step, bool multiplyStep = false);
        static EnjoLib::VecF GetSpaceRandom(float valMin, float valMax, int number = 100);

        const IDataProvider * m_per;
        EnjoLib::Str varId;

        float valMin;
        float valMax;
        float step;
        bool multiplyStep;
        bool fp;
    protected:
    private:
        float val;
        float valDefault;
};

//typedef OptiVar<int> OptiVarInt;
//typedef OptiVar<bool> OptiVarBool;
//typedef OptiVarF OptiVarF;

#endif // OPTIVARTPL_H
