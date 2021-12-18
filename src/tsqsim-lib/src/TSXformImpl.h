#ifndef TSXFORMIMPL_H
#define TSXFORMIMPL_H

#include "ITSXform.h"
#include "typesStr.h"

struct TSXformDiff : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        unsigned MaxShift() const override;
        double Invert(const EnjoLib::VecD & vals) const override;
};

struct TSXformFabs : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;
};

struct TSXformSqrtSafe : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;
};

struct TSXformLogSafe : public ITSXform
{
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;
        
        static constexpr double VAL_BORDER = 1;
};

struct TSXformAdd : public ITSXform
{
        TSXformAdd(const VecStr & params);
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;

        double m_add = 0;
};

struct TSXformMul : public ITSXform
{
        TSXformMul(const VecStr & params);
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;

        double m_mul = 0;
};

struct TSXformDiv : public ITSXform
{
        TSXformDiv(const VecStr & params);
        double Run(const TSFunBase & input, int idx, double valPrev) const override;
        double Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals) const override;

        double m_div = 0;
};

#endif // TSXFORMIMPL_H
