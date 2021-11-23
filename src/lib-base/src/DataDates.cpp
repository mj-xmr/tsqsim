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
