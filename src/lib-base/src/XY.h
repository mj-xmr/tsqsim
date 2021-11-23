#ifndef XY_H
#define XY_H

struct XY
{
    XY(int x = 0, float y = 0) : x(x), y(y){}
    virtual ~XY(){}

    bool operator < (const XY & other) const;
    bool IsValid() const;
    int x;
    float y;
};

#include "Direction.h"
struct XYDir : public XY
{
    XYDir(int i, float val, Direction dir)
    : XY(i, val)
    , m_dir(dir)
    {

    }
    Direction m_dir = SELL;
};

#endif // XY_H
