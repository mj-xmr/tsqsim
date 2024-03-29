#ifndef PREDICTORUTIL_H
#define PREDICTORUTIL_H

#include <Util/VecFwd.hpp>
#include <cstdlib>

class ITSFun;

class PredictorUtil
{
    public:
        PredictorUtil();
        virtual ~PredictorUtil();

        EnjoLib::VecD Regression(int numSamples, const EnjoLib::VecD & data, bool erratic0 = false) const;
        EnjoLib::VecD SimpleMA  (int numSamples, const EnjoLib::VecD & data, bool erratic0 = false) const;
        EnjoLib::VecD GetErrorsCorrected(const EnjoLib::VecD & pred, const EnjoLib::VecD & data) const;
        
        double RegressionProt(int numSamples, const EnjoLib::VecD & data, size_t idx, bool erratic0 = false) const;

    protected:
        
        
        double SimpleMAProt  (int numSamples, const EnjoLib::VecD & data, size_t idx, bool erratic0 = false) const;
        double Erratic(const EnjoLib::VecD & data, size_t idx, bool erratic0) const;

    private:
};

#endif // PREDICTORUTIL_H
