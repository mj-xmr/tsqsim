#ifndef TIMEUTIL_H
#define TIMEUTIL_H


class TimeUtil
{
    public:
        TimeUtil();
        virtual ~TimeUtil();
        
        int GetCurrentHour() const;
        int GetCurrentYear() const;
        int GetCurrentMonth() const;
        int GetCurrentTimeComponent(const char fmt) const;

    protected:

    private:
};

#endif // TIMEUTIL_H
