#ifndef DATADATES_H
#define DATADATES_H


class DataDates
{
    public:
        DataDates();
        virtual ~DataDates() {}

        void Set0();
        void SetStart(int year, int month);
        void SetEnd(int year, int month);

        long int yearStart;
        long int yearEnd;
        long int monthStart;
        long int monthEnd;

    protected:

    private:
};

#endif // DATADATES_H
