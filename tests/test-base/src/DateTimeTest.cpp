#include "pch_test.h"
#include "DateTimeTest.h"
#include <UnitTest++/UnitTest++.h>

#include <DateTime.h>

DateInt gdate1 = 20140701040000;
DateInt gdate2 = 23141202140200;
DateInt gdate3 = 20150119181234;
DateInt gdate3_dateOnly = 20150119000000;
DateInt gdate3_timeOnly = 181234;

TEST(DateTime_GetYear1)
{
    DateTime date(gdate1);
    int result = date.GetYear();
    int expected = 2014;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetYear2)
{
    DateTime date(gdate2);
    int result = date.GetYear();
    int expected = 2314;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetMonth1)
{
    DateTime date(gdate1);
    int result = date.GetMonth();
    int expected = 7;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetMonth2)
{
    DateTime date(gdate2);
    int result = date.GetMonth();
    int expected = 12;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetDay1)
{
    DateTime date(gdate1);
    int result = date.GetDay();
    int expected = 1;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetDay2)
{
    DateTime date(gdate2);
    int result = date.GetDay();
    int expected = 2;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetHour1)
{
    DateTime date(gdate1);
    int result = date.GetHour();
    int expected = 4;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetHour2)
{
    DateTime date(gdate2);
    int result = date.GetHour();
    int expected = 14;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetMinute1)
{
    DateTime date(gdate1);
    int result = date.GetMinute();
    int expected = 0;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_GetMinute2)
{
    DateTime date(gdate2);
    int result = date.GetMinute();
    int expected = 2;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_FilterDateOnly)
{
    DateTime date(gdate3);
    DateInt result = date.GetDateOnly(true);
    DateInt expected = gdate3_dateOnly;
    CHECK_EQUAL(expected, result);
}

TEST(DateTime_FilterTimeOnly)
{
    DateTime date(gdate3);
    DateInt result = date.GetTimeOnly();
    DateInt expected = gdate3_timeOnly;
    CHECK_EQUAL(expected, result);
}
