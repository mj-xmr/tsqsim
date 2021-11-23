#ifndef INTERESTMAN_H
#define INTERESTMAN_H

#include <Template/CacheRAMBase.hpp>
#include <Util/Str.hpp>
#include "Interest.h"

class InterestMan
{
    public:
        InterestMan();
        virtual ~InterestMan(){}

        float GetBid(const EnjoLib::Str & symbol, DateInt date) const;
        float GetAsk(const EnjoLib::Str & symbol, DateInt date) const;
        float GetMid(const EnjoLib::Str & symbol, DateInt date) const;

        bool HasSymbol(const EnjoLib::Str & symbol) const;

    protected:

    private:
        const Interest & GetInterest(const EnjoLib::Str & symbol, DateInt date) const;
        EnjoLib::CacheRAMBasePtr<EnjoLib::Str, stdfwd::vector<Interest>> m_interest;
};

#endif // INTERESTMAN_H
