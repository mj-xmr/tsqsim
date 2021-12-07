#ifndef TSXFORMIMPL_H
#define TSXFORMIMPL_H

#include "ITSXform.h"
#include "typesStr.h"

struct TSXformDiff : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        unsigned MaxShift() const override;
        double Invert(const EnjoLib::VecD & vals) const override;
};

struct TSXformFabs : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
};

struct TSXformSqrt : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
};

struct TSXformSqrtSafe : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
};

struct TSXformLogSafe : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Invert(const EnjoLib::VecD & vals) const override;
};

struct TSXformAdd : public ITSXform
{
        TSXformAdd(const VecStr & params);
        double Run(const TSFunBase & input, int idx, double valPrev) const override;

        double m_add = 0;
};

#endif // TSXFORMIMPL_H
