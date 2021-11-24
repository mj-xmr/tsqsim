#include "TSFunFactory.h"

#include "TSFunPrintAll.h"
#include "TSFunPrintCumul.h"
#include "TSFunXForm.h"
#include "TSFunLua.h"
#include "TSFunTxt.h"

#include <Util/Except.hpp>

TSFunFactory::TSFunFactory(){}
TSFunFactory::~TSFunFactory(){}

CorPtr<ITSFun> TSFunFactory::Create(const TSInput & tsin, const TSFunType & type) const
{
    switch (type)
    {
    case TSFunType::PRINT_ALL:      return CorPtr<ITSFun>(new TSFunPrintAll(tsin));
    case TSFunType::PRINT_CUMUL:    return CorPtr<ITSFun>(new TSFunPrintCumul(tsin));
    case TSFunType::XFORM:          return CorPtr<ITSFun>(new TSFunXForm(tsin));
    case TSFunType::LUA:            return CorPtr<ITSFun>(new TSFunLua(tsin));
    case TSFunType::TXT:            return CorPtr<ITSFun>(new TSFunTxt(tsin));
    }
    
    throw EnjoLib::ExceptNotImpl("Not handled type");
}
