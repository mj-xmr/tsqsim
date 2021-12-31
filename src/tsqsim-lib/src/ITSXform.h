#ifndef ITSXFORM_H
#define ITSXFORM_H

#include <Util/VecD.hpp>

class IHasCandles;
struct XformRes;

struct ITSXform
{
        ITSXform();
        virtual ~ITSXform();

        virtual XformRes Run(const IHasCandles & input, int idx, double prevConverted) const = 0; /// TODO: remove valPrev
        virtual XformRes Run(const EnjoLib::VecD & vals) const = 0;
        virtual double Invert(const EnjoLib::VecD & vals, double lost) const = 0;

        /// virtual double Invert(const IHasCandles & input, int idx) const = 0; /// TODO HI-level iface
        virtual unsigned MaxShift() const;

        double GetVal(const IHasCandles & input, int idx) const;
};

#endif // ITSXFORM_H
