#ifndef CROSSVALIDCALC_H
#define CROSSVALIDCALC_H

#include "StartEnd.h"

struct OptiXValid
{
    StartEnd opti;
    StartEnd xvalid;
    StartEnd GetBoth() const;
    bool operator== (const OptiXValid & other) const;

    bool isValid = false;
};

class IHasLen;
class IPeriod;
class ConfigOpti;

class CrossValidCalc
{
    public:
        CrossValidCalc(const IHasLen & len, const IPeriod & per, const ConfigOpti & confOpti);
        CrossValidCalc(int totallen, int m_numBarsOpti, float percentAhead, bool isLast);
        virtual ~CrossValidCalc();


        StartEnd GetUpToNumber(int progress) const;
        OptiXValid GetPass(int i) const;
        OptiXValid GetPassLast() const;

    protected:

    private:
        OptiXValid GetPassPriv(int i) const;

        int m_totallen = 0;
        int m_numBarsOpti = 0;
        int m_numBarsAhead = 0;
};

#endif // CROSSVALIDCALC_H
