#ifndef SIMULATORTSREPORTS_HPP
#define SIMULATORTSREPORTS_HPP

#include <Util/StrFwd.hpp>
#include <Util/VecFwd.hpp>
#include <Template/ArrayFwd.hpp>

class ConfigTS;
class IDataProvider;

class SimulatorTSReports
{
    public:
        SimulatorTSReports();
        virtual ~SimulatorTSReports();

        EnjoLib::VecD PrepPredsPlot(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred) const;
        void PrintReportSingleThreaded(const IDataProvider & per, const ConfigTS & cfgTS, const EnjoLib::VecD & data, const EnjoLib::Str & descr,
                                       const EnjoLib::Array<const EnjoLib::VecD *> & plots) const;

        void PrintOpti(const EnjoLib::VecD & predsPlot) const;

    protected:

    private:
};

#endif // SIMULATORTSREPORTS_HPP
