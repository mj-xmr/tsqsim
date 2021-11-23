#ifndef IHASDATECOMPONENTS_H
#define IHASDATECOMPONENTS_H

#include <Util/Str.hpp>

class IHasDateComponents
{
    public:
        IHasDateComponents();
        virtual ~IHasDateComponents();

        virtual int GetYear() const = 0;
        virtual int GetMonth() const = 0;
        virtual int GetDay() const = 0;
        virtual int GetHour() const = 0;
        virtual int GetMinute() const = 0;
        virtual int GetSecond() const = 0;
        EnjoLib::Str GetISODateTime() const;

    protected:
    private:
};

#endif // IHASDATECOMPONENTS_H
