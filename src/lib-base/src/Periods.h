#ifndef PERIODS_H
#define PERIODS_H

#include <Template/VecT.hpp>
class ISymbol;

class PeriodsAll
{
public:
    PeriodsAll();
    virtual ~PeriodsAll();
    const EnjoLib::VecT<int> & GetPeriods() const {return periods;}

private:
    EnjoLib::VecT<int> periods;
};

#define TSQ_PERIOD_CLASS(className) \
template <class PeriodClass> \
class className : public PeriodClass \
{ \
    public: \
        className(const ISymbol & sym); \
        virtual ~className() {} \
        float GetMaxLossPercent() const override; \
};

TSQ_PERIOD_CLASS(Minute1)
TSQ_PERIOD_CLASS(Minute5)
TSQ_PERIOD_CLASS(Minute15)
TSQ_PERIOD_CLASS(Minute30)
TSQ_PERIOD_CLASS(Hour1)
TSQ_PERIOD_CLASS(Hour2)
TSQ_PERIOD_CLASS(Hour4)
TSQ_PERIOD_CLASS(Hour8)
TSQ_PERIOD_CLASS(Hour12)
TSQ_PERIOD_CLASS(Day)
TSQ_PERIOD_CLASS(Week)
TSQ_PERIOD_CLASS(Month)

#endif // PERIODS_H
