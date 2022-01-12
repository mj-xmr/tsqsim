#ifndef IOPTIMIZER_H
#define IOPTIMIZER_H

#include "IHasLen.h"
#include <Math/MultiDimIter/IMultiDimIterConsumerTpl.hpp>
#include <Util/VecD.hpp>
#include <Template/ArrayFwd.hpp>

class OptiVarF;

class IOptimizer : public IHasLen, public EnjoLib::IMultiDimIterConsumerTpl
{
    public:
        IOptimizer();
        virtual ~IOptimizer();
        
        virtual void operator()() = 0;
        virtual void SetSilent() = 0;
        virtual EnjoLib::Array<OptiVarF *> GetResult() = 0;
        virtual EnjoLib::VecD GetResultVec() const = 0;

    protected:

    private:
};

#endif // IOPTIMIZER_H
