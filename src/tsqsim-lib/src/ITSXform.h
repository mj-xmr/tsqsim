#ifndef ITSXFORM_H
#define ITSXFORM_H

class TSFunBase;

struct ITSXform
{
        ITSXform();
        virtual ~ITSXform();

        virtual double Run(const TSFunBase & input, int idx, double valPrev) const = 0;
        /// virtual double Invert(const TSFunBase & input, int idx, double valPrev) const = 0; /// TODO HI
        virtual unsigned MaxShift() const;
};

#endif // ITSXFORM_H
