#ifndef TSXFORMIMPL_H
#define TSXFORMIMPL_H

#include "ITSXform.h"
#include "typesStr.h"

struct TSXformOrig : public ITSXform
{
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;
};

struct TSXformDiff : public ITSXform
{
        TSXformDiff(const VecStr & params);
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        unsigned MaxShift() const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;
        
        int m_order = 1;
};

struct TSXformFabs : public ITSXform
{
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;
};

struct TSXformSqrt : public ITSXform
{
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;
};

struct TSXformLog : public ITSXform
{
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;
        
        static constexpr double VAL_BORDER = 1;
};

struct TSXformAdd : public ITSXform
{
        TSXformAdd(const VecStr & params);
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;

        double m_add = 0;
};

struct TSXformMul : public ITSXform
{
        TSXformMul(const VecStr & params);
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;

        double m_mul = 0;
};

struct TSXformDiv : public ITSXform
{
        TSXformDiv(const VecStr & params);
        XformRes Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const override;
        XformRes Run(const EnjoLib::VecD & vals) const override;
        double Invert(const EnjoLib::VecD & vals, double lost) const override;

        double m_div = 0;
};

#endif // TSXFORMIMPL_H
