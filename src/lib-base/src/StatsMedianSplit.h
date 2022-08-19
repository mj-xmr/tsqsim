#ifndef STATSMEDIANSPLIT_H
#define STATSMEDIANSPLIT_H

class IDataProvider;

#include <Template/VecT.hpp>
#include <Util/VecD.hpp>
#include <Util/StrFwd.hpp>

class StatsMedianSplit
{
    public:
        StatsMedianSplit(bool multiThreaded = false);
        virtual ~StatsMedianSplit();

        struct Results
        {
            double mean = 0;
            double dev = 0;
            double urt = 0;
            int num = 0;
            EnjoLib::VecT<int> nums = 0;
            EnjoLib::VecD means, devs, urts;
        };

        Results CalcResults(const IDataProvider & dat, int numRanges) const;
        void Stats(const IDataProvider & dat, int numRanges = 3) const;

        Results CalcResults(const EnjoLib::VecD & dat, int numRanges) const;
        void Stats(const EnjoLib::Str & idd, const EnjoLib::VecD & dat, int numRanges = 3) const;

        EnjoLib::Str Report(const EnjoLib::Str & idd, const Results & res) const;

    protected:

    private:
        bool m_multiThreaded = false;
};

#endif // STATSMEDIANSPLIT_H
