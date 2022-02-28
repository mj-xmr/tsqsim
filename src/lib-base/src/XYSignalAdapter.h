#ifndef XYSIGNALADAPTER_H
#define XYSIGNALADAPTER_H

#include "XYPairDir.h"
#include <3rdParty/stdfwd.hh>
#include <Template/ArrayFwd.hpp>
#include <Util/Pair.hpp>
class ISignal;
class IHasXYPair;

class XYSignalAdapter
{
    public:
        XYSignalAdapter();
        virtual ~XYSignalAdapter();

        EnjoLib::Array<XYPairDir> GetPlotXY(const ISignal & sig, const IHasXYPair & ihxy) const;

    protected:

    private:
};

#endif // XYSIGNALADAPTER_H
