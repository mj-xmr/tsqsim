#ifndef SRFINAL_H
#define SRFINAL_H

#include "Direction.h"
#include <3rdParty/stdfwd.hh>

class SRFinal
{
    public:
        SRFinal(float level = 0, Direction dir = SELL, bool broken = false, bool touched = false, int iStart = 0, int iEnd = 0);
        virtual ~SRFinal();

        float GetLevel() const { return m_level; }
        Direction GetDir() const { return m_dir; }
        bool IsBroken() const { return m_broken; }
        bool IsTouched() const { return m_touched; }
        int GetStart() const { return m_iStart; }
        int GetEnd() const { return m_iEnd; }
        unsigned GetId() const { return m_id; }
        void SetEnd(int iEnd) { m_iEnd = iEnd; }
        void AdvanceIndex();

        typedef stdfwd::multimap<float, SRFinal> SrFinType; // Sorted by SRFinal->GetStart()
        //typedef SrFinType::const_iterator SFCIt;
        //typedef SrFinType::iterator SFIt;
    protected:
    private:
        float m_level;
        Direction m_dir;
        bool m_broken;
        bool m_touched;
        int m_iStart;
        int m_iEnd;
        unsigned m_id = 0;
};

#endif // SRFINAL_H
