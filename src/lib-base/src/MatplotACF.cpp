#include "MatplotACF.h"
#include "ConfigDirs.h"

#include <Ios/Osstream.hpp>
#include <Ios/Ofstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/AlgoSTDIVec.hpp>
#include <Util/ToolsMixed.hpp>

#include <cstdlib>
using namespace EnjoLib;

MatplotACF::MatplotACF(){}
MatplotACF::~MatplotACF(){}

void MatplotACF::Plot(const EnjoLib::VecD & dat, int lags, const EnjoLib::Str & title) const
{
    const ConfigDirs cfgDirs;
    const Str pyModuleIn = cfgDirs.DIR_SCRIPTS2 + "plot_acf_pacf.py";
    {
        Ifstream ifs(pyModuleIn);
    }
    const VecStr & linesModule = Tokenizer().GetLines(pyModuleIn);
    const Str scriptOut = ToolsMixed().GetTmpDir() + "/plot_acf_pacf_out.py";
    {
        Ofstream ofs(scriptOut);
        ofs << "import matplotlib" << Nl;
        //ofs << "matplotlib.use('Agg')" << Nl; // For screenshots

        for (const Str & line : linesModule)
        {
            ofs << line << Nl;
        }
        VecD reversed = dat;
        AlgoSTDIVec<double>().Reverse(&reversed);
        //ofs << dat.PrintPython("dat") << Nl;
        ofs << reversed.PrintPython("dat") << Nl;
        ofs <<  "plotACF(dat, " << lags << ", '" << title << "')" << Nl;
        ofs << "plotPACF(dat, " << lags << ", '" << title << "')" << Nl;
    }

    ToolsMixed().SystemCallWarn("python3 " + scriptOut, "MatplotACF::Plot()");
}
