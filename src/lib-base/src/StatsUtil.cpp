#include "StatsUtil.h"

#include "Logic.h"
#include <Util/AlgoSTDIVec.hpp>

using namespace std;
using namespace EnjoLib;

StatsUtil::StatsUtil(){}
StatsUtil::~StatsUtil(){}

StatsUtil::Distrib StatsUtil::GetDistrib(const EnjoLib::VecD & data, int numBins) const /// TODO: Upstream
{
    Distrib distrib;
    EnjoLib::VecD dataSorted = data;
    AlgoSTDIVec<double>().Sort(&dataSorted);
    if (dataSorted.size() < 2)
    {
        return distrib;
    }
    const double lo = dataSorted.First();
    const double hi = dataSorted.Last();
    const double rangeDiff = hi - lo;
    const double binLen = rangeDiff / double(numBins);
    //const int nbinLo = gm.round((lo-rangeLo) / binLen);
    //const int nbinHi = gm.round((hi-rangeLo) / binLen);

    for (int i = 1; i < numBins; ++i)
    {
        const double valMin = lo + binLen * (i - 1);
        const double valMax = lo + binLen * (i);
        const double valMid = (valMax + valMin) / 2.0;
        int numOcurrences = 0;
        for (const double val : dataSorted)
        {
            if (valMin <= val && val <= valMax)
            {
                ++numOcurrences;
            }
            else
            {
                if (numOcurrences > 0)
                    break; // ?
            }
        }
        distrib.data.push_back(MakePair(valMid, static_cast<double>(numOcurrences)));
    }
    return distrib;
}

bool StatsUtil::Distrib::IsValid() const
{
    return data.size() >= 2;
}
