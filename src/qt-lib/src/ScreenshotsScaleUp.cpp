#include "pch_qt.h"

#include "ScreenshotsScaleUp.h"
#include "MyMainWindow.h"

#include <ISymbol.h>
#include <IPeriod.h>
#include <PeriodUtil.h>
//#include "PlotData.h" /// Drags too many dependencies (from TF)
#include "PlotDataScreenshot.h"
#include <ConfigGlob.h>
#include <ConfigDirs.h>
#include <ConfigMan.h>
#include <ConfigTF2.h>
#include <ConfigSym.h>
#include <ConfigQT.h>
#include <ConfigQTPlot.h>
//#include <Consts.h>
#include <TradeUtil.h>
//#include <TradeUtilDepend.h>
#include "IMainTester.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
//#include "PeriodFactory.h"
//#include "SymbolFactory.h"
#include <IBufferCandles.h>
#include "TSUtil.h"
#include "ISimulatorTS.h"
#include "BufferVecType.h"
#include "BufferType.h"
#include "DataSrcType.h"
#include "SymbolFactoryAbstract.h"
#include "StrategyFactoryAbstract.h"

#include <EnjoLibBoost/Filesystem.hpp>

#include <Template/Array.hpp>
#include <Template/CorradePointer.h>
#include <Util/Time.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/LinuxSystemCalls.hpp>
#include <Util/ProtocolCreatorFile.hpp>
#include <Util/Except.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;
void ScreenshotsScaleUp::Handle(MyMainWindow * win, int mode,
                        const EnjoLib::Str & symName,  const EnjoLib::Str & periodName,
                        const EnjoLib::Str & ssOutDir, const EnjoLib::Str & dataInputFileName) const
{
    {LOGL << "Screenshot " << symName << "-" << periodName << " outdir = " << ssOutDir << Endl;}


    ELO
    const CharManipulations cmp;
    VecStr periods;
    /*
    const EnjoLib::Array<EnjoLib::Str> & periodsS = GetPeriods(periodName);

    for (auto s : periodsS)
        periods.push_back(s);
    */
    periods.push_back("h1"); /// TODO: Restore from above
    //const bool useTechs = false;

    //const bool isRemoveFile = mode == 6;
    //cout << "Scale up\n";
    const int width = 400;


    /// TODO: Restore
    //Corrade::Containers::Pointer<ISymbol> symbol = PeriodUtil().LoadSymbolFromFileMT(*win->m_mons.m_symFact, symName, periods, dataInputFileName, false);

    //const SymbolFactory symFact;
    const SymbolFactoryAbstract & symFact = *(win->m_mons.m_symFact);
    const ConfigTF2 & cfgTF2 = *gcfgMan.cfgTF2;
    ConfigSym & cfgSym = *gcfgMan.cfgSym;
    ConfigQT & cfgQT = *gcfgMan.cfgQT;
    ConfigQTPlot & cfgQTPlot = *gcfgMan.cfgQTPlot;

    cfgQTPlot.DAY_WEEK = true;

    //cfgSym.SetDataSrc()
    cfgQT.bufRainbow = int(BufferVecTypeEnum::BUF_VEC_STATION_PRED);
    cfgQT.buf1 = int(BufferTypeEnum::BUF_NONE);
    cfgQT.buf2 = int(BufferTypeEnum::BUF_SPREADS_BULL);
    cfgQT.buf3 = int(BufferTypeEnum::BUF_SPREADS);
    cfgSym.period = periods.at(0);
    EnjoLib::Pair<int, int> yearMonth = TradeUtil().GetYearMonthMax(symName);
    {
        cfgSym.dates.monthEnd  = yearMonth.second;
        cfgSym.dates.yearEnd   = yearMonth.first;
        LOGL << "Using latest date. " << cfgSym.dates.ToStr() << Nl;
    }

    const CorPtr<IMainTester> mtest = IMainTester::Create(symFact, &cfgTF2);
    VecStr pers; pers.push_back(periodName);
    CorPtr<ISymbol> symbol = mtest->GetSymbol(symName, pers);
    symbol->FinalizeCandle();

    LOG << "ScreenshotsScaleUp::Handle(): Init data size = " << symbol->GetPeriod(periods.at(0)).Len() << Endl;
    symbol->LimitData(width);
    const EnjoLib::Str & dateTimeTrue = Time().TimeStampToHuman(std::time(NULL), "%Y.%m.%d %H;%M");
    EnjoLib::Str dateTime = dateTimeTrue;
    dateTime.at(dateTime.size()-1) = '0'; // Change the last minute's digit to 0 for simplicity
    const EnjoLib::Str & dirSub  = "/Screenshots/";
    const EnjoLib::Str & outDir  = ssOutDir.empty() ? ("." + dirSub) : ssOutDir;
    const EnjoLib::Str & dirN    = ssOutDir + "/n/" + dirSub;
    const EnjoLib::Str & dirM    = ssOutDir + "/m/" + dirSub;
    const EnjoLib::Str & dirNorm = ssOutDir + "/"   + dirSub;

    for (const EnjoLib::Str & dir : std::vector<EnjoLib::Str>{dirN, dirM, dirNorm})
    {
        Filesystem().CreateDir(dir.c_str());
        ProtocolCreatorFile fileFlag(dir + "/" + dateTime + "-" + symbol->GetName() + "-R.txt");
    }
    symbol->CalcTech();
    win->SetDark(true);
    for (const EnjoLib::Str & periodName : periods)
    {
        ELO
        const IPeriod & period = symbol->GetPeriod(periodName);
        LOG << "Per " << period.GetName() << ", len = " << period.Len() << Endl;
        win->setupWindow();
        QCustomPlot * p = win->GetQCP();
        p->setNotAntialiasedElements(QCP::AntialiasedElement::aeAll);

        const EnjoLib::Str & idd = cmp.ToUpper(period.GetSymbolPeriodId());
        //const auto type = StrategyFactory::Type::STRA_DUMMY; /// TODO: Segfaults
        const auto type = StrategyFactory::Type::STRA_SR_BRK;
        auto strat = win->m_mons.m_stratFact->Create(type, period);


        const PlotDataBase * data = nullptr;
        //if (useTechs)
            //data = new PlotData(period, *strat); // More noise
        //else
            data = new PlotDataScreenshot(period);
        auto m_d = Corrade::Containers::Pointer<const PlotDataBase>(data);
        CorPtr<ISimulatorTS> simTS = TSUtil().GetSim(period);
        win->setupBaustelle(p, period, *strat, *simTS, *m_d);

        //p->rescaleAxes(); // doesn't help
        p->replot();


        //const EnjoLib::Str & fName = dateTime + "-" + idd;
        const EnjoLib::Str & fName = idd + "-Cyclic";
        //cout << fname << endl;
        SavePNG(p, dirNorm + fName, 1850, 850);
        SavePNG(p, dirM    + fName, 1000, 410);
        SavePNG(p, dirN    + fName, 820,  1050);
    }
    //if (isRemoveFile)
    {
        //std::remove(dataInputFileName.c_str()); // NEVER REMOVE FILES! Left for MT
    }
    //qApp->quit();
    exit(0);
}

void ScreenshotsScaleUp::SavePNG(QCustomPlot * p, const EnjoLib::Str & pathPar, int w, int h) const
{
    const CharManipulations cmp;
    const EnjoLib::Str & ext = ".png";
    const EnjoLib::Str & path = cmp.Replace(pathPar, "-D-", "-D1-");
    const EnjoLib::Str & fullPath = (path + ext).c_str();
    LOGL << "Storing to " << fullPath << Endl;
    p->savePng(fullPath.c_str(), w, h);
    LinuxSystemCalls::OptiPNG(fullPath);
}

std::vector<EnjoLib::Str> ScreenshotsScaleUp::GetPeriods(const EnjoLib::Str & periodName) const
{
    const CharManipulations cmp;
    //const EnjoLib::Str & perNameHuman = TradeUtil().MinutesToPeriodName(cmp.ToInt(periodName));
    const EnjoLib::Str & perNameHuman = periodName;
    const std::vector<EnjoLib::Str> periodsLo {"m15", "m30", "h1"};
    //const VecStr periodsLo {"m30", "h1", "h4"};
    //const VecStr periodsLo {"h1", "h4", "d"};
    const std::vector<EnjoLib::Str> periodsHi {"h4", "h8", "d"};

    if (perNameHuman == periodsLo.at(0))
        return periodsLo;
    else if (perNameHuman == periodsHi.at(0))
        return periodsHi;
    else
        throw EnjoLib::ExceptInvalidArg("Period = " + periodName + " is neither " + periodsLo.at(0) + " nor " + periodsHi.at(0));
}
