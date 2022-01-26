#ifndef STATSUTIL_H
#define STATSUTIL_H

#include <Util/VecD.hpp>
#include <Util/Pair.hpp>
#include <STD/Vector.hpp>

class StatsUtil
{
    public:
        StatsUtil();
        virtual ~StatsUtil();

        struct Distrib
        {
            std::vector<EnjoLib::Pair<double, double>> data;
            bool IsValid() const;
        };
        Distrib GetDistrib(const EnjoLib::VecD & data, int numBins = 30) const; /// TODO: Upstream

    protected:

    private:
};

#endif // STATSUTIL_H
