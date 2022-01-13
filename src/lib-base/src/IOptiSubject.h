#ifndef IOPTISUBJECT_H
#define IOPTISUBJECT_H

#include "OptiVar.h"
#include <Math/Opti/OptiMultiSubject.hpp>

class IOptiSubject : public EnjoLib::OptiMultiSubject
{
    public:
        IOptiSubject();
        virtual ~IOptiSubject();
        
        virtual STDFWD::vector<OptiVarF> GetOptiVarsResult() = 0;

    protected:

    private:
};

#endif // IOPTISUBJECT_H
