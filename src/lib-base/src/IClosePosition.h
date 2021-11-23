#ifndef ICLOSEPOSITION_H
#define ICLOSEPOSITION_H


#include "SignalBase.h"

class IStrategy;

class IClosePosition : public SignalBase
{
    public:
        IClosePosition(const IStrategy & strat);
        virtual ~IClosePosition();

        const IStrategy & GetStrat() const { return m_strat; };
        virtual unsigned LenProt() const override;
    protected:

    private:

        const IStrategy & m_strat;
};

#endif // ICLOSEPOSITION_H
