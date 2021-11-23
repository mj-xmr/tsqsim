#ifndef XYPAIRDIR_H
#define XYPAIRDIR_H

#include "XY.h"
#include "Direction.h"
#include "State.h"
class Candle;

class XYPairDir
{
    public:
        XYPairDir();
        XYPairDir(XY one, XY two, State st);
        XYPairDir(XY one, XY two, Direction dir);
        virtual ~XYPairDir();

        bool IsValid() const;
        Candle GetRange() const;
        double GetDiff(bool percent) const;
        bool IsOtherInThis(const XYPairDir & tested) const;

        XY one, two;
        Direction bullish;


    protected:

    private:
};

#endif // XYPAIRDIR_H
