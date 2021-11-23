#ifndef ESTIMUTIL_H
#define ESTIMUTIL_H

#include <XYd.h>
#include <Template/CacheRAMBase.hpp>
#include <Template/Array.hpp>
#include <Util/Pair.hpp>

class IDataProvider;
class EstimUtil
{
    public:
        EstimUtil(const IDataProvider & dat);
        virtual ~EstimUtil();

        EnjoLib::Array<XYd> GetSamplesTargetsXY(int sooner, int later) const;

    protected:

    private:
        EnjoLib::Array<XYd> GetPrice(int sooner, int later) const;
        EnjoLib::Array<XYd> GetEMA(int sooner, int later) const;

        const IDataProvider & m_dat;
        
        mutable EnjoLib::CacheRAMBasePtr<EnjoLib::Pair<int, int>, EnjoLib::Array<XYd>> m_cache;
};

#endif // ESTIMUTIL_H
