#include "GnuplotIOSWrap.h"

#include <EnjoLibBoost/gnuplot-iostream.h>

#include <Math/GeneralMath.hpp>
#include <Ios/Osstream.hpp>
#include <Template/Array.hpp>

#include <STD/Tuple.hpp>

using namespace gnuplotio;

const int GnuplotIOSWrap::TERMINAL_W = 110;
const int GnuplotIOSWrap::TERMINAL_H = 24;

GnuplotIOSWrap::~GnuplotIOSWrap(){}
GnuplotIOSWrap::GnuplotIOSWrap()
: m_gnuplot((new Gnuplot()))
{}

void GnuplotIOSWrap::Cmd(const EnjoLib::Str & cmd)
{
    (*m_gnuplot) << cmd << '\n';
}

///SetupY()
void GnuplotIOSWrap::Add1d(const EnjoLib::VecD & data)
{
    m_gnuplot->send1d(data);
}

///SetupXY()
void GnuplotIOSWrap::Add2d(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & data)
{
    std::vector<std::tuple<double, double>> dataTuple;
    for (const auto & par : data)
    {
        dataTuple.push_back(std::make_tuple(par.first, par.second));
    }
    m_gnuplot->send1d(dataTuple);
}

void GnuplotIOSWrap::SetupTerminal(float scaleX, float scaleY)
{
    if (scaleX != 1 && scaleY == 1)
    {
        scaleY = scaleX; // User scaled X, but not Y, so scale both proportionally
    }
    const EnjoLib::GMat gmat;
    const int xxx = gmat.round(TERMINAL_W * scaleX);
    const int yyy = gmat.round(TERMINAL_H * scaleY);
    EnjoLib::Osstream oss;
    oss << "set terminal dumb " << xxx << " " << yyy;
    Cmd(oss.str());
}
void GnuplotIOSWrap::SetupY()
{
    Cmd("plot '-' using 1 with lines notitle");
}
void GnuplotIOSWrap::SetupXY()
{
    Cmd("plot '-' with lines notitle");
}

void GnuplotIOSWrap::SetZeroMin(double valMax)
{
    EnjoLib::Osstream oss;
    oss << "set yrange [0:" << valMax << "]";
    //gpl.Cmd("set yrange [0:*]");
    Cmd(oss.str());
}

void GnuplotIOSWrap::SetZeroMin()
{
    Cmd("set yrange [0:*]");
}

void GnuplotIOSWrap::SetMinMax(double valMin, double valMax)
{
    EnjoLib::Osstream oss;
    oss << "set yrange [" << valMin << ":" << valMax << "]";
    Cmd(oss.str());
}

void GnuplotPlotTerminal1d(const EnjoLib::VecD & data, const EnjoLib::Str & descr, float scaleX, float scaleY)
{
    if (not descr.empty())
    {
        std::cout << descr << '\n';
    }
    if (data.size() < 3)
    {
        return;
    }
    GnuplotIOSWrap plot;
    plot.SetupTerminal(scaleX, scaleY);
    plot.SetupY();
    plot.Add1d(data);
}

void GnuplotPlotTerminal2d(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::FP, EnjoLib::FP>> & data, const EnjoLib::Str & descr, float scaleX, float scaleY)
{
    if (not descr.empty())
    {
        std::cout << descr << '\n';
    }
    if (data.size() < 3)
    {
        return;
    }
    GnuplotIOSWrap plot;
    plot.SetupTerminal(scaleX, scaleY);
    plot.SetupXY();
    plot.Add2d(data);
}

void GnuplotPlotTerminal1dSubplots(const EnjoLib::Array<const EnjoLib::VecD *> & data, const EnjoLib::Str & descr, float scaleX, float scaleY)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        EnjoLib::Str descrUsed = "";
        if (i == 0)
        {
            descrUsed = descr;
        }
        GnuplotPlotTerminal1d(*data.at(i), descrUsed, scaleX, scaleY);
    }
}
