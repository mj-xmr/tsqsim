#ifndef TICKSPROVIDERTXTADHOC_H
#define TICKSPROVIDERTXTADHOC_H

#include "TicksProviderGenerated.h"


class TicksProviderTxtAdHoc : public TicksProviderGenerated
{
    public:
        TicksProviderTxtAdHoc();
        virtual ~TicksProviderTxtAdHoc();
        
        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;

    protected:

    private:
};

#endif // TICKSPROVIDERTXTADHOC_H
