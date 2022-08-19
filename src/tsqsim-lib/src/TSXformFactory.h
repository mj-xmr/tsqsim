#ifndef TSXFORMFACTORY_H
#define TSXFORMFACTORY_H

#include "ITSXform.h"
#include <Util/StrFwd.hpp>
#include <Util/VecStr.hpp>
#include <Template/CorradePointer.h>

enum class TSXformType;

class TSXformFactory
{
    public:
        TSXformFactory();
        virtual ~TSXformFactory();
        
        CorPtr<ITSXform> Create(const EnjoLib::Str & name) const;
        CorPtr<ITSXform> CreateByType(const TSXformType & type, const VecStr & params) const; // Not extensible.

    protected:

    private:
};

#endif // TSXFORMFACTORY_H
