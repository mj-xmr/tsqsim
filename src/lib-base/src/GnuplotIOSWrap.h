#ifndef GNUPLOTIOSWRAP_H
#define GNUPLOTIOSWRAP_H

#include <Template/SafePtr.hpp>
#include <Template/ArrayFwd.hpp>
#include <Util/Pair.hpp>
#include <Util/Str.hpp>
#include <Util/VecFwd.hpp>

namespace gnuplotio
{
    class Gnuplot;
}


class GnuplotIOSWrap
{
    public:
        GnuplotIOSWrap();
        virtual ~GnuplotIOSWrap();
        void SetupTerminal(float scaleX = 1, float scaleY = 1);
        void SetupY();
        void SetupXY();
        void Cmd(const EnjoLib::Str & cmd);
        void SetMinMax(double valMin, double valMax);
        void SetZeroMin(double valMax);
        void SetZeroMin();
        void Add1d(const EnjoLib::VecD & data);
        void Add2d(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & data);

        const static int TERMINAL_W;
        const static int TERMINAL_H;


    protected:

    private:
        EnjoLib::SafePtr<gnuplotio::Gnuplot> m_gnuplot;

};
void GnuplotPlotTerminal1d(const EnjoLib::VecD & data, const EnjoLib::Str & descr = "", float scaleX = 1, float scaleY = 1);
void GnuplotPlotTerminal2d(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & data, const EnjoLib::Str & descr = "", float scaleX = 1, float scaleY = 1);
void GnuplotPlotTerminal1dSubplots(const EnjoLib::Array<const EnjoLib::VecD *> & data, const EnjoLib::Str & descr = "", float scaleX = 1, float scaleY = 1);

#endif // GNUPLOTIOSWRAP_H
