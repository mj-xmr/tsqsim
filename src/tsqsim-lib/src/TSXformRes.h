#ifndef XFORMRES1_H
#define XFORMRES1_H

//#include <Util/VecD.hpp>

//#include <STD/Map.hpp>

class IHasCandles;
class ITSXform;

struct XformRes
{
    explicit XformRes(double conv = 0) : conv(conv){}
    double conv = 0;
    double lost = 0;
};


#endif // XFORMRES_H
