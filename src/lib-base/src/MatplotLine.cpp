#include "MatplotLine.h"
#include "ConfigDirs.h"

#include <Ios/Osstream.hpp>
#include <Ios/Ofstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/ToolsMixed.hpp>

#include <cstdlib>
using namespace EnjoLib;

MatplotLine::MatplotLine(){}
MatplotLine::~MatplotLine(){}

void MatplotLine::AddLine(const EnjoLib::VecD & line, const EnjoLib::Str & descr, const EnjoLib::Str & colour)
{
    Data dat;
    dat.data = line;
    dat.descr = descr;
    dat.colour = colour;
    m_dat.push_back(dat);
}

void MatplotLine::Plot(const EnjoLib::Str & title) const
{
    const ConfigDirs cfgDirs;
    const Str pyModuleIn = cfgDirs.DIR_SCRIPTS2 + "plot_line.py";
    {
        Ifstream ifs(pyModuleIn);
    }
    const VecStr & linesModule = Tokenizer().GetLines(pyModuleIn);
    const Str scriptOut = ToolsMixed().GetTmpDir() + "/plot_line_out.py";
    {
        Ofstream ofs(scriptOut);
        ofs << "import matplotlib" << Nl;
        //ofs << "matplotlib.use('Agg')" << Nl; // For screenshots

        for (const Str & line : linesModule)
        {
            ofs << line << Nl;
        }

        ofs << "lines = PlotLine()" << Nl;
        ofs << "legend = [";
        for (const Data & dat : m_dat)
        {
            ofs << "'" << dat.descr << "', " << Nl;
        }
        ofs << "]" << Nl;


        for (const Data & dat : m_dat)
        {
            ofs << dat.data.PrintPython("dat") << Nl;
            ofs << "lines.addData1(dat, '" << dat.colour << "')" << Nl;
        }
        ofs << "lines.setupFigure('" << title << "', legend)" << Nl;
        ofs << "lines.show()" << Nl;
        ofs << "lines.close()" << Nl;
        //ofs << "lines.demo()" << Nl;
    }

    ToolsMixed().SystemCallWarn("python3 " + scriptOut, "MatplotLine::Plot()");
}
