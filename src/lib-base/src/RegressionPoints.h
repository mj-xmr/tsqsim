#ifndef REGRESSIONPOINTS_H
#define REGRESSIONPOINTS_H

#include "typesVec.h"
#include <Template/VecT.hpp>
#include <Util/Pair.hpp>


class IDataProvider;
class RegressionPoints
{
    public:
        RegressionPoints();
        virtual ~RegressionPoints();

        float GetPoints() const;
        void AddPoint(const IDataProvider & period, int j, float valCurr, float diffLoMin, float diffHiMax);
        void Finish();
        void Plot() const;
        float GetMedian() const;
        float GetDistribDiff(const RegressionPoints & other) const;
        float GetAvgSpread() const;
        float GetMaxSpread() const;
        float GetRange() const;

    protected:

    private:
        double GetNormalDistrib(double x) const;
        STDFWD::vector<EnjoLib::Pair<double, double>> GetDistrib() const;

        static const int m_numBins;

        EnjoLib::VecT<int> m_distributionIn;
        EnjoLib::VecD m_distributionOut;

        Vec m_vValCurr;
        Vec m_vHi;
        Vec m_vLo;
};

#endif // REGRESSIONPOINTS_H
