#include "DTWIDistComp.h"
#include "DTWDistType.h"
#include <Util/Except.hpp>
#include <Util/CharManipulations.hpp>
#include <Template/CorradePointer.h>

DTWIDistComp::DTWIDistComp()
{
    //ctor
}

DTWIDistComp::~DTWIDistComp()
{
    //dtor
}

#include "DTWDistCompDTW.h"
CorPtr<DTWIDistComp> DTWIDistComp::Create(const DTWDistType & type, const EnjoLib::VecD & obsNew)
{
    switch (type)
    {
    case DTWDistType::DTWType:
        return CorPtr<DTWIDistComp>(new DTWDistCompDTW(obsNew));
    case DTWDistType::KNNType:
        return CorPtr<DTWIDistComp>(new DTWDistCompKNN(obsNew));
    }
    throw EnjoLib::ExceptRuntimeError("Not handled DTWDistType: " + EnjoLib::CharManipulations().ToStr(int(type)));
}
    