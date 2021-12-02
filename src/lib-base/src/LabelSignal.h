#ifndef LABELSIGNAL_H
#define LABELSIGNAL_H

#include <Util/Str.hpp>
#include "types.h"
#include "Direction.h"
class IDataProvider;

class LabelSignal
{
    public:
        LabelSignal();
        LabelSignal(const IDataProvider & period, DateInt dt, Direction dir);
        virtual ~LabelSignal();

        //void SetDate(DateInt dt);
        DateInt GetDate() const { return m_date; };
        bool IsBullish() const { return m_dir == BUY; }
        Direction GetDir() const { return m_dir; }
        bool IsValid() const;
        EnjoLib::Str GetSymbolPeriodId() const;
        EnjoLib::Str GetId() const;

        bool operator < (const LabelSignal & other) const;

    protected:

    private:
        DateInt m_date = 0;
        Direction m_dir;
        EnjoLib::Str m_symbolPeriodId;
};

#endif // LABELSIGNAL_H
