#ifndef PERIODGAPFINDER_H
#define PERIODGAPFINDER_H

class IPeriod;
class PeriodGapFinder
{
    public:
        PeriodGapFinder(const IPeriod & per);
        virtual ~PeriodGapFinder(){}

        void Print() const;

    protected:

    private:
        const IPeriod & m_per;
};

#endif // PERIODGAPFINDER_H
