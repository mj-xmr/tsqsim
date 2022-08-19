#ifndef DATADATES_H
#define DATADATES_H

#include <Util/StrFwd.hpp>

class DataDates
{
    public:
        DataDates();
        virtual ~DataDates() {}

        void Set0();
        void SetNoEnd();
        void SetStart(int year, int month);
        void SetEnd(int year, int month);
        void UpdateIfNot0(const DataDates & other);
        static void UpdateVarIfNot0(const long int src, long int * var);
        
        EnjoLib::Str ToStr() const;

        long int yearStart;
        long int yearEnd;
        long int monthStart;
        long int monthEnd;

    protected:


    private:
};

#endif // DATADATES_H
