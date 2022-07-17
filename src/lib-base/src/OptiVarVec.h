#ifndef OPTIVARVEC_H
#define OPTIVARVEC_H

#include "OptiVar.h"
#include <Util/Pimpl.hpp>
#include <Template/Iters2.hpp>
#include <Template/ArrayFwd.hpp>

class OptiVarVec
{
    public:
        OptiVarVec();
        OptiVarVec(const STDFWD::initializer_list<OptiVarF *> & invec);
        virtual ~OptiVarVec();

        void Add(OptiVarF * var);
        void Reinit(EnjoLib::Array<OptiVarF *> & vopti);

        int size() const;

        //OptiVarVecInternal vec;

        STDFWD::vector<OptiVarF *> & VecRW();
        EnjoLib::Array<OptiVarF *> Vec() const;

        /*
        typedef EnjoLib::Iter<OptiVarF *>              iterator;
        typedef EnjoLib::Iter<const OptiVarF *>        const_iterator;

        const_iterator       begin() const;
        const_iterator       end() const;

        iterator             begin();
        iterator             end();
        const_iterator       cbegin() const;
        const_iterator       cend() const;
        */

    protected:

    private:
        PIMPL_CPY
};


//using OptiVarVec = OptiVarVecInternal;

#endif // OPTIVARVEC_H
