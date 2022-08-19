#ifndef TYPESVEC_H_INCLUDED
#define TYPESVEC_H_INCLUDED

#include "types.h"
//

namespace EnjoLib
{
    //class VecF;
    //class VecD;
}

#include <Util/VecD.hpp>
#include <Util/VecFwd.hpp>
#include <Template/VecT.hpp>
#include <Template/VectorViewableFwd.hpp>
#include <Template/IIterableFwd.hpp>

typedef EnjoLib::VecT<int> VecI;
typedef EnjoLib::VecF Vec;
//typedef EnjoLib::VecD VecD;
typedef STDFWD::vector<bool> VecB;
//typedef VecB Mask;
typedef EnjoLib::VecD Mask;
typedef STDFWD::vector<Candle> VecCan;
typedef EnjoLib::VectorViewable<Candle> VecCanView;
typedef EnjoLib::IIterableConst<Candle> IterCan;


#endif // TYPESVEC_H_INCLUDED
