#ifndef LABEL_H
#define LABEL_H

#include "types.h"

class Label
{
    public:
        Label();
        Label(DateInt dstart, DateInt dend);
        virtual ~Label();

        void SetStart(DateInt dt);
        void SetEnd(DateInt dt);
        DateInt GetStart() const { return m_start; };
        DateInt GetEnd() const { return m_end; };
        bool IsValid() const;

        bool operator < (const Label & other) const;

    protected:
    private:
        DateInt m_start = 0;
        DateInt m_end = 0;
};

#endif // LABEL_H
