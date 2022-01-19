#ifndef TICKSPROVIDERGENERATED_H
#define TICKSPROVIDERGENERATED_H

#include <TicksProviderFake.h>


class TicksProviderGenerated : public ITicksProvider
{
    public:
        TicksProviderGenerated();
        virtual ~TicksProviderGenerated();
        
        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;
        bool IsGenerated() const override { return true; }

    protected:

    private:
};

#endif // TICKSPROVIDERGENERATED_H
