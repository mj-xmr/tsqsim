#ifndef LABELQTSIGNAL_H
#define LABELQTSIGNAL_H

#include <LabelSignal.h>
#include <3rdParty/stdfwd.hh>

class IPeriod;
class IStrategy;

class LabelQTSignal : public LabelSignal
{
    public:
        LabelQTSignal(const IPeriod & period, const IStrategy & strat, DateInt dt, Direction dir);
        virtual ~LabelQTSignal();
        EnjoLib::Str ToString() const;
    protected:
    private:
        const IPeriod & m_period;
        const IStrategy & m_strat;
};

#endif // LABELQTSIGNAL_H
