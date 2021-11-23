#ifndef LEVERAGES_H
#define LEVERAGES_H

#include <Util/Str.hpp>
#include <Template/CacheRAMBase.hpp>

class Leverages
{
    public:
        Leverages();
        virtual ~Leverages();
        float GetLeverage(const EnjoLib::Str & symbolName) const;
    protected:
    private:
        EnjoLib::CacheRAMBasePtr<EnjoLib::Str, float> m_mapLeverages;
};

#endif // LEVERAGES_H
