#include "PredictorPyCustom.h"

#include "ConfigDirs.h"
#include "ConfigMan.h"
#include "ConfigTS.h"
#include "StrUtil.h"

#include <Ios/Osstream.hpp>
#include <Ios/Ofstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/AlgoSTDIVec.hpp>
#include <Util/ToolsMixed.hpp>

using namespace EnjoLib;

PredictorPyCustom::PredictorPyCustom(const IDataProvider & dat)
: PredictorBase(dat, "PyCustom")
{
}

PredictorPyCustom::~PredictorPyCustom()
{
}

bool PredictorPyCustom::IsCustomScript() const
{
    return true;
}


EnjoLib::VecD PredictorPyCustom::PredictVec(const EnjoLib::VecD & data) const
{ 
    const EnjoLib::VecD & vec = ExePython(data);
    return vec;
}

double PredictorPyCustom::PredictNext(const BufferDouble & datExpanding) const
{
    const EnjoLib::VecD & vec = ExePython(datExpanding.GetData(), false);
    return vec.Last();
}

EnjoLib::VecD PredictorPyCustom::ExePython(const EnjoLib::VecD & data, bool movingWindow) const
{
    const ConfigDirs dirs;
    const Str pyModuleInStatic = dirs.DIR_SCRIPTS2 + "py_static.py";
    const Str pyModuleIn = gcfgMan.cfgTS->m_scriptPathTxtPy;
    {
        Ifstream ifs1(pyModuleIn);
        Ifstream ifs2(pyModuleInStatic);
    }
    ELO
    LOG << "Reading file: " << pyModuleIn << Nl;
    const Tokenizer tok;
    const VecStr & linesModule = tok.GetLines(pyModuleIn);
    const VecStr & linesStatic = tok.GetLines(pyModuleInStatic);
    const Str scriptOut = ToolsMixed().GetTmpDir() + "py_custom.py";
    const Str scriptExchange = scriptOut + "-exchange.txt";
    {
        Ofstream ofs(scriptOut);
        ofs << "import matplotlib" << Nl;
        //ofs << "matplotlib.use('Agg')" << Nl; // For screenshots
        
        //VecD reversed = data;
        //AlgoSTDIVec<double>().Reverse(&reversed);
        //ofs << dat.PrintPython("dat") << Nl;
        ofs << data.PrintPython("dat") << Nl;
        ofs << "lag = " << GetLags() << Nl;
        ofs << "OUT_FILE = '" << scriptExchange << "'" << Nl;
        ofs << "IS_MOVING_WINDOW = " << (movingWindow ? "True" : "False") << Nl;
        
        StrUtil().WriteLines(linesStatic, ofs);
        StrUtil().WriteLines(linesModule, ofs);
        //ofs <<  "plotACF(dat, " << lags << ", '" << title << "')" << Nl;
        //ofs << "plotPACF(dat, " << lags << ", '" << title << "')" << Nl;
        //ofs << "plotSeasonalDecomposition(dat, " << periodSeasonal << ", '" << title << "')" << Nl; /// TODO: Different lags for seasonality. It's the period. Do in wx.
    }
    LOG << "Wrote file: " << scriptOut << Nl;
    ToolsMixed().SystemCallThrow("python3 " + scriptOut, "PredictorPyCustom::PredictVec()");
    
    const VecStr & linesOut = tok.GetLines(scriptExchange);
    const EnjoLib::VecD ret(linesOut.at(0));
    return ret;
}

unsigned PredictorPyCustom::GetLags() const
{
    return 2;
    return GetLag1().GetVal();
}
