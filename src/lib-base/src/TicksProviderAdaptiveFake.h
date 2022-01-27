#ifndef TICKSPROVIDERADAPTIVEFAKE_H
#define TICKSPROVIDERADAPTIVEFAKE_H

#include <ITicksProvider.h>


class TicksProviderAdaptiveFake : public ITicksProvider
{
    public:
        TicksProviderAdaptiveFake();
        virtual ~TicksProviderAdaptiveFake();

        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;

    protected:

    private:
};

#endif // TICKSPROVIDERADAPTIVEFAKE_H
