#ifndef DATETIME_H
#define DATETIME_H

#include "types.h"
#include "IHasDateComponents.h"

class DateTime : public IHasDateComponents
{
    public:
        DateTime(DateInt date);
        virtual ~DateTime();

        int GetYear() const override;
        int GetMonth() const override;
        int GetDay() const override;
        int GetHour() const override;
        int GetMinute() const override;
        int GetSecond() const override;
        DateInt GetDateInt() const { return m_date; }
        DateInt GetDateOnly(bool addTrailingZeroes) const;
        int GetTimeOnly() const;

    protected:
    private:
        int ShiftExtract2(DateInt date, uint64_t divisor) const;

        DateInt m_date;
};

#endif // DATETIME_H
