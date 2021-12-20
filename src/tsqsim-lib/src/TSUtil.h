#ifndef TSUTIL_H
#define TSUTIL_H

#include <Template/CorradePointerFwd.h>

class IPeriod;
class ISimulatorTS;

class TSUtil
{
    public:
        TSUtil();
        virtual ~TSUtil();

        CorPtr<ISimulatorTS> GetSim(const IPeriod & per) const;

    protected:

    private:
};

#endif // TSUTIL_H
