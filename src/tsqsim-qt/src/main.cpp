/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 11.10.14                                             **
**          Version: 1.3.0-beta                                           **
****************************************************************************/
#include "pch_qt.h"

#include "MyMainWindow.h"
#include "Monster.h"
#include "CLITsq.h"
#include "CLIResult.h"
#include <StrategyFactoryDummy.h>
#include <SymbolFactoryClean.h>
#include <ConfigMan.h>
#include <ConfigQT.h>
#include <ConfigSym.h>
#include "StrategyType.h"
#include "StrategyTypeEnum.h"

//#include <Util/Trim.hpp>
#include <Util/CharManipulations.hpp>

#include <QApplication>

#include <cstdio>
#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;

int main(int argc, char *argv[])
{
    int mode = 0;
    if (argc > 1)
    {
        /// TODO: Restore?
        //mode = CharManipulations().ToInt(argv[1]);
    }
    // Experiment:
    const CLITsq cli;
    const EnjoLib::Result<CLIResult> & result = cli.GetConfigs(argc, argv);
    if (not result.isSuccess)
    {
        return 0;
    }
    //screenShot = true;
    const EnjoLib::Str screenShotOutDir  = argc > 2 ? argv[2] : "";
    const EnjoLib::Str screenShotSymbol  = argc > 3 ? argv[3] : "";
    const EnjoLib::Str screenShotPeriod  = argc > 4 ? argv[4] : "";
    const EnjoLib::Str dataInputFileName = argc > 5 ? argv[5] : "";

    EnjoLib::Str symName = "AUDUSD-min";
    EnjoLib::Str periodName = "h2";
    StrategyType stratType = StrategyFactory::Type::STRA_SR_BRK;
    gcfgMan.Read();
    ConfigSym * pconf = gcfgMan.cfgSym.get();
    pconf->UpdateFromOther(result.value.m_confSym);
    pconf->Write(); // Propagates the CLI choices
     
    //const ConfigTF2 & confTF2 = *gcfgMan.cfgTF2;
    //const ConfigOpti & confOpti = *gcfgMan.cfgOpti;
    try
    {
        //cout << "Reading config" << endl;
        stratType =     pconf->GetStrat();
        symName =       pconf->symbol;
        periodName =    pconf->period;
        //m_percentBars = pconf->percentBars;
        //m_barNum =      pconf->barNum;
    }
    catch(...)
    {
        LOGL << "Couldn't read config\n";
        exit(1);
    }


    Monster mon(screenShotOutDir, screenShotSymbol, screenShotPeriod, dataInputFileName);
    mon.SetStratFactory(new StrategyFactoryDummy());
    mon.SetSymFactory  (new SymbolFactoryClean());
    mon.Reload(symName, periodName, stratType, mode);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QApplication::setGraphicsSystem("raster");
#endif
    /// TODO: Check it it's useful:
    QApplication a(argc, argv);

    //cout << "mode = " << mode << "\nscreenShotOutDir = " << screenShotOutDir << "\nscreenShotSymbol = " << screenShotSymbol << "\nscreenShotPeriod = " << screenShotPeriod << "\ndataInputFileName = " << dataInputFileName << endl;
    MyMainWindow w;
    w.Reload(mon, mode);
    w.show();

    return a.exec();
}
