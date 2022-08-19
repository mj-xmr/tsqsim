#ifndef LABELQT_H
#define LABELQT_H

#include <types.h>
#include <Label.h>
#include <Util/StrFwd.hpp>

class IPeriod;

class LabelQT : public Label
{
    public:
        LabelQT(const IPeriod & period);
        virtual ~LabelQT();
        EnjoLib::Str ToString() const;
    protected:
    private:
        const IPeriod & m_period;
};

#endif // LABELQT_H
