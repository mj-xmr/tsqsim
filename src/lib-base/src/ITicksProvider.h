#ifndef ITICKSPROVIDER_H
#define ITICKSPROVIDER_H

#include <Util/StrFwd.hpp>
#include <Template/CorradePointer.h>

class ITicks;
class ConfigSym;
class ITicksProvider
{
    public:
        ITicksProvider();
        virtual ~ITicksProvider();
        virtual CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const = 0;
        virtual CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const = 0;
        
        virtual bool IsGenerated() const { return false; }

    protected:
    private:
};

#endif // ITICKSPROVIDER_H
