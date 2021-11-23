#ifndef DAYOFWEEKCANDLE_H
#define DAYOFWEEKCANDLE_H

#include <EnjoLibBoost/DayOfWeek.hpp>
class Candle;
class DayOfWeekCandle : public EnjoLib::DayOfWeek
{
    public:
        DayOfWeekCandle(const Candle & can);
        virtual ~DayOfWeekCandle();

    protected:

    private:
};

#endif // DAYOFWEEKCANDLE_H
