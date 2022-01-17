#ifndef TICKSPROVIDERGENERATED_H
#define TICKSPROVIDERGENERATED_H

#include <TicksProviderFake.h>


class TicksProviderGenerated : public TicksProviderXMRFake
{
    public:
        TicksProviderGenerated();
        virtual ~TicksProviderGenerated();
        
        bool IsFake() const override { return true; }

    protected:

    private:
};

#endif // TICKSPROVIDERGENERATED_H
