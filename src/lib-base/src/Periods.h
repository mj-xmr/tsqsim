#ifndef PERIODS_H
#define PERIODS_H

class ISymbol;

template <class PeriodClass>
class Minute1 : public PeriodClass
{
    public:
        Minute1(const ISymbol & sym);
        virtual ~Minute1() {}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Minute5 : public PeriodClass
{
    public:
        Minute5(const ISymbol & sym);
        virtual ~Minute5() {}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Minute15 : public PeriodClass
{
    public:
        Minute15(const ISymbol & sym);
        virtual ~Minute15(){}
        float GetTPRatio() const override;
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Minute30 : public PeriodClass
{
    public:
        Minute30(const ISymbol & sym);
        virtual ~Minute30(){}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Hour1 : public PeriodClass
{
    public:
        Hour1(const ISymbol & sym);
        virtual ~Hour1(){}
        float GetTPRatio() const override;
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Hour2 : public PeriodClass
{
    public:
        Hour2(const ISymbol & sym);
        virtual ~Hour2(){}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Hour4 : public PeriodClass
{
    public:
        Hour4(const ISymbol & sym);
        virtual ~Hour4(){}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Hour8 : public PeriodClass
{
    public:
        Hour8(const ISymbol & sym);
        virtual ~Hour8(){}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Hour12 : public PeriodClass
{
    public:
        Hour12(const ISymbol & sym);
        virtual ~Hour12(){}
        float GetMaxLossPercent() const override;
};

template <class PeriodClass>
class Day : public PeriodClass
{
    public:
        Day(const ISymbol & sym);
        virtual ~Day(){}
        float GetMaxLossPercent() const override;
};

#endif // PERIODS_H
