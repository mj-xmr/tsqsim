#ifndef IOPTIMIZABLE_H
#define IOPTIMIZABLE_H

#include "types.h"
//#include <vector>

#include <Template/IIterableFwd.hpp>

//template<class T> class OptiVarF;

class OptiVarF;
class OptiVarVec;
class IOptimizable
{
    public:
        IOptimizable();
        virtual ~IOptimizable();

        
        //virtual std::vector<OptiVarF *> GetOptiFloat() = 0;
        virtual OptiVarVec GetOptiFloat() = 0;
        
        void ReinitVars();
        void UpdateOptiVars(const EnjoLib::IIterable<OptiVarF *> & opti);

    protected:
    private:
};

#endif // IOPTIMIZABLE_H
