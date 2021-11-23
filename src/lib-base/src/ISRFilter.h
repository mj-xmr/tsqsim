#ifndef ISRFILTER_H
#define ISRFILTER_H

class SRFinal;
class State;
class ISRFilter
{
    public:
        ISRFilter();
        virtual ~ISRFilter();
        virtual bool IsOK(const State & st, const SRFinal & srFin) const = 0;

    protected:

    private:
};

#endif // ISRFILTER_H
