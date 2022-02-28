#ifndef IHASXYPAIR_H
#define IHASXYPAIR_H

#include <3rdParty/stdfwd.hh>
#include <Template/ArrayFwd.hpp>
#include <Util/Pair.hpp>
class XYPairDir;
class State;

class IHasXYPair
{
    public:
        IHasXYPair();
        virtual ~IHasXYPair();
        virtual EnjoLib::Array<XYPairDir> GetPlotXY() const = 0;
        virtual XYPairDir GetPrevCurrXY(const State & st) const = 0;

    protected:

    private:
};

#endif // IHASXYPAIR_H
