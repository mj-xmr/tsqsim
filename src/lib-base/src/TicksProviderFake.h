#ifndef TICKSPROVIDERFAKE_H
#define TICKSPROVIDERFAKE_H

#include "ITicksProvider.h"

#include "typesStr.h"

class ConfigSym;
class TicksProviderFake : public ITicksProvider
{
    public:
        TicksProviderFake(){}
        virtual ~TicksProviderFake(){}

        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;
        bool IsGenerated() const override { return true; }

        VecStr Generate() const;
    protected:
    private:
};

class TicksProviderXMRFake : public ITicksProvider
{
    public:
        TicksProviderXMRFake(){}
        virtual ~TicksProviderXMRFake(){}

        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;

        bool IsGenerated() const override { return true; }

        VecStr Generate() const;

    protected:
    private:
};

class TicksProviderOrderedSeriesFake : public ITicksProvider
{
    public:
        TicksProviderOrderedSeriesFake(){}
        virtual ~TicksProviderOrderedSeriesFake(){}

        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;

        bool IsGenerated() const override { return true; }

        VecStr Generate() const;

    protected:
    private:
};

#endif // TICKSPROVIDERFAKE_H
