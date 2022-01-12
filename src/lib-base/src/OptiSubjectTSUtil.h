#ifndef OPTISUBJECTTSUTIL_H
#define OPTISUBJECTTSUTIL_H

#include "OptiVar.h"
#include <Math/Opti/OptiMultiSubject.hpp>

class IOptimizable;

class OptiSubjectTSUtil
{
    public:
        OptiSubjectTSUtil();
        virtual ~OptiSubjectTSUtil();
        
        double UpdateOptiGetPenality(const double * in, int n, const EnjoLib::VecD & iterData, IOptimizable * opti) const;
        
        EnjoLib::VecD GetStartProt(const STDFWD::vector<OptiVarF> & optiVec) const;
        EnjoLib::VecD GetStepProt(const STDFWD::vector<OptiVarF> & optiVec) const;
        EnjoLib::Array<EnjoLib::OptiMultiSubject::Bounds> GetBoundsProt(const STDFWD::vector<OptiVarF> & optiVec) const;
        
    protected:
        

    private:
};

#endif // OPTISUBJECTTSBASE_H
