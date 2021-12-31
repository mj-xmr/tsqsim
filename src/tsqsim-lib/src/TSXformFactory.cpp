#include "TSXformFactory.h"

#include "TSXformImpl.h"
#include "TSXformTypeString.h"
#include "TSXformType.h"

#include <Util/Except.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>

using namespace EnjoLib;

TSXformFactory::TSXformFactory(){}
TSXformFactory::~TSXformFactory(){}

CorPtr<ITSXform> TSXformFactory::Create(const Str & name) const
{
    const CharManipulations cman;

    const VecStr & tokens = Tokenizer().Tokenize(name);
    const Str namelo = cman.ToLower(tokens.at(0));

    VecStr params;
    for (unsigned i = 1; i < tokens.size(); ++i)
    {
        params.push_back(tokens.at(i));
    }
    const TSXformTypeString typeStr;
    if (typeStr.HasName(namelo))
    {
        const TSXformType type = typeStr.ToType<TSXformType>(namelo);
        return CreateByType(type, params);
    }

    throw ExceptNotImpl("Not implemented ISXform: '" + namelo + "'");
}

CorPtr<ITSXform> TSXformFactory::CreateByType(const TSXformType & type, const VecStr & params) const
{
    switch (type)
    {
        case TSXformType::ORIG:     return CorPtr<ITSXform>(new TSXformOrig());
        case TSXformType::DIFF:     return CorPtr<ITSXform>(new TSXformDiff(params));
        case TSXformType::FABS:     return CorPtr<ITSXform>(new TSXformFabs());
        case TSXformType::SQRTS:    return CorPtr<ITSXform>(new TSXformSqrt());
        case TSXformType::LOGS:     return CorPtr<ITSXform>(new TSXformLog());
        case TSXformType::ADD:      return CorPtr<ITSXform>(new TSXformAdd(params));
        case TSXformType::MUL:      return CorPtr<ITSXform>(new TSXformMul(params));
        case TSXformType::DIV:      return CorPtr<ITSXform>(new TSXformDiv(params));
        case TSXformType::END:      return CorPtr<ITSXform>(new TSXformDiff(params)); // Fake
    }

    throw ExceptNotImpl("Not implemented ISXform: '" + CharManipulations().ToStr(int(type)) + "'");
}
