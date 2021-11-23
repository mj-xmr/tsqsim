#ifndef OPTIMIZERUTILS_H
#define OPTIMIZERUTILS_H

#include <Util/Str.hpp>
class IDataProvider;

class OptimizerUtils
{
    public:
        OptimizerUtils();
        virtual ~OptimizerUtils();

        EnjoLib::Str GetVarBaseDir(bool release) const;
        EnjoLib::Str GetVarDir(const IDataProvider & period, bool release) const;
        EnjoLib::Str GetVarPath(const IDataProvider & period, const EnjoLib::Str & varId, bool release) const;

    protected:
    private:
};

#endif // OPTIMIZERUTILS_H
