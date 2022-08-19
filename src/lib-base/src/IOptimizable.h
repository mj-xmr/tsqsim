#ifndef IOPTIMIZABLE_H
#define IOPTIMIZABLE_H

#include "types.h"
//#include <vector>

#include <Util/VecFwd.hpp>
#include <Util/StrFwd.hpp>
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
        virtual OptiVarVec GetOptiFloat() = 0; /// TODO: Provide a const ret method and a conversion from OptiVarF * to const OptiVarF * to return it. Same in Symbol
        
        EnjoLib::VecD GetOptiVec();
        void ReinitVars();
        void UpdateOptiVars(const EnjoLib::IIterable<OptiVarF *> & opti);
        void UpdateOptiVars(const EnjoLib::VecD & optiVarsLoopData);
        void PrintOptiVars(const EnjoLib::Str & context);

    protected:
    private:
};

#endif // IOPTIMIZABLE_H
