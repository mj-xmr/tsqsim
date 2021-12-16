#include "TSXformFactory.h"

#include "TSXformImpl.h"
#include "TSXformTypeString.h"
#include "TSXformType.h"

#include <Util/Except.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>

using namespace EnjoLib;

TSXformFactory::TSXformFactory()
{
    //ctor
}

TSXformFactory::~TSXformFactory()
{
    //dtor
}

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
        switch (type)
        {
            case TSXformType::DIFF:     return CorPtr<ITSXform>(new TSXformDiff());
            case TSXformType::FABS:     return CorPtr<ITSXform>(new TSXformFabs());
            case TSXformType::SQRTS:    return CorPtr<ITSXform>(new TSXformSqrtSafe());
            case TSXformType::LOGS:     return CorPtr<ITSXform>(new TSXformLogSafe());
            case TSXformType::ADD:      return CorPtr<ITSXform>(new TSXformAdd(params));
            case TSXformType::END:      return CorPtr<ITSXform>(new TSXformDiff()); // Fake
        }
    }

    throw ExceptNotImpl("Not implemented ISXform: '" + namelo + "'");
}
