#include "DataDates.h"

DataDates::DataDates()
{
    yearStart   = 2016;
    yearEnd     = 2017;
    monthStart  = 1;
    monthEnd    = 12;
}

void DataDates::Set0()
{
    yearStart = yearEnd = monthStart = monthEnd = 0;
}

void DataDates::SetStart(int year, int month)
{
    yearStart = year;
    monthStart = month;
}

void DataDates::SetEnd(int year, int month)
{
    yearEnd = year;
    monthEnd = month;
}

void DataDates::UpdateIfNot0(const DataDates & other)
{
    UpdateVarIfNot0(other.yearStart,    &yearStart);
    UpdateVarIfNot0(other.yearEnd,      &yearEnd);
    UpdateVarIfNot0(other.monthStart,   &monthStart);
    UpdateVarIfNot0(other.monthEnd,     &monthEnd);
}

void DataDates::UpdateVarIfNot0(const long int src, long int * var)
{
    if (src != 0)
    {
        (*var) = src;
    }
}
