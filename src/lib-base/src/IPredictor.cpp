#include "IPredictor.h"
#include "BufferDouble.h"

using namespace EnjoLib;

const double IPredictor::ERROR = 0; // Try for example -10000 as well, or a boolean EnjoLib::Result

IPredictor::IPredictor(){}
IPredictor::~IPredictor(){}

/*
double IPredictor::PredictNext(const EnjoLib::VecD & orig, const EnjoLib::VecD & data, size_t idx) const
{
    if (idx >= data.size())
    {
        return 0;
    }
    const VecD & ret = Predict(orig, data, idx, 1);
    return ret.at(0);
}
*/
/*
EnjoLib::VecD IPredictor::PredictNextVec(const EnjoLib::VecD & orig, const EnjoLib::VecD & data) const
{
    VecD ret;
    for (size_t i = 0; i < data.size(); ++i)
    {
        const double pred = PredictNext(orig, data, i);
        ret.Add(pred);
    }
    return ret;
}
*/

EnjoLib::VecD IPredictor::Predict(const EnjoLib::VecD & data) const
{
    VecD ret;
    VecD input;
    for (size_t i = 0; i < data.size(); ++i)
    {
        input.Add(data.at(i));
        
        if (i < GetLags())
        {
            ret.Add(IPredictor::ERROR);
        }
        else
        {
            BufferDouble buf(input, "predictor");
            const double pred = PredictNext(buf);
            ret.Add(pred);
        }
    }
    return ret;
}

EnjoLib::VecD IPredictor::PredictVec(const EnjoLib::VecD & data)  const
{
    //return EnjoLib::VecD();
    return Predict(data);
}