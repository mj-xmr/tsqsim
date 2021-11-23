#ifndef IHASCANDLESACCESS_H
#define IHASCANDLESACCESS_H

class IBufferCandles;
#include "State.h"
#include <Util/VecF.hpp>

struct VecHiding
{
    VecHiding(int type) : type(type) {}
    float operator[] (const State & st) const;
    EnjoLib::VecF m_data;
    int type;
};

class IHasCandlesAccess
{
    public:
        IHasCandlesAccess(const IBufferCandles & bufCan);
        virtual ~IHasCandlesAccess();


    protected:
        VecHiding Open;
        VecHiding Close;
        VecHiding High;
        VecHiding Low;
        constexpr static float Point = 0.00001;
    private:
};

#endif // IHASCANDLESACCESS_H
