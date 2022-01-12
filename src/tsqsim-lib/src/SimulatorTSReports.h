#ifndef SIMULATORTSREPORTS_HPP
#define SIMULATORTSREPORTS_HPP

#include <Util/VecD.hpp>

class ConfigTS;
class IDataProvider;

class SimulatorTSReports
{
    public:
        SimulatorTSReports();
        virtual ~SimulatorTSReports();

        EnjoLib::VecD PrepPredsPlot(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred) const;
        void PrintReportSingleThreaded(const IDataProvider & per, const ConfigTS & cfgTS, const EnjoLib::VecD & data, const EnjoLib::Str & descr,
                                       const STDFWD::vector<const EnjoLib::VecD *> & plots) const;
                                       
        void PrintOpti(const EnjoLib::VecD & predsPlot) const;

        bool VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2, double eps = 0) const; /// TODO: Extractg

    protected:

    private:
};

#endif // SIMULATORTSREPORTS_HPP
