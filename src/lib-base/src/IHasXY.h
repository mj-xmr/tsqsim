#ifndef IHASXY_H
#define IHASXY_H

#include <3rdParty/stdfwd.hh>
#include <Template/ArrayFwd.hpp>

class XY;
class State;

class IHasXY
{
    public:
        IHasXY();
        virtual ~IHasXY();

        virtual EnjoLib::Array<XY> GetPlotXY(const State & st) const = 0;

    protected:

    private:
};

#endif // IHASXY_H
