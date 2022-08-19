#include "CLITsq.h"
#include "TSXformTypeString.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Template/Array.hpp>

using namespace EnjoLib;

CLITsq::CLITsq(){}
CLITsq::~CLITsq(){}

EnjoLib::Str CLITsq::GetAdditionalHelp() const
{
    Osstream oss;
    const TSXformTypeString types;
    oss << "Available transformations for text-based scripting:\n";
    for (const Str & name : types.GetNames())
    {
        oss << name << " ";
    }
    
    return oss.str();
}
