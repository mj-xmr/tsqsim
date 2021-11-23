#ifndef XYD_H
#define XYD_H

struct XYd
{
    XYd(double x = 0, double y = 0) : x(x), y(y){}
    virtual ~XYd(){}

    bool operator < (const XYd & other) const;
    double x;
    double y;
};

#endif // XYD_H
