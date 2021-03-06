#include "pch_qt.h"

#include "MyMainWindow.h"
#include "PeriodUtil.h"
#include "PlotElements.h"
#include "SymbolFactoryAbstract.h"
#include "ConfigMan.h"
#include "ConfigSym.h"
#include "DataSrcType.h"
#include "IStrategy.h"
#include <ISymbol.h>
#include <Template/CorradePointer.h>


using namespace std;


Corrade::Containers::Pointer<ISymbol> MyMainWindow::LoadSymbolFromFile() const
{
    const EnjoLib::Str symName = "EURUSD";
    const EnjoLib::Str periodName = "h4";
    const EnjoLib::Str dataDir = "static/data-test/sr/";
    //const EnjoLib::Str dataFile = dataDir + "eurusd-2018-02-standard.txt";
    const EnjoLib::Str dataFile = "data/periodDump.txt";

    VecStr pers; pers.push_back(periodName);
    Corrade::Containers::Pointer<ISymbol> psym = PeriodUtil().LoadSymbolFromFile(*m_mons.m_symFact, symName, pers, dataFile, true);
    return psym;
}

QCPAxisRect * MyMainWindow::SetupTechs(QCustomPlot * p, const IStrategy & strat, const ISimulatorTS & simTS, const PlotDataBase & d, bool dark)
{
    PlotElements pel;
    QCPAxisRect * techRect = pel.SetupGetIndicatorRect(p, d);
    switch (gcfgMan.cfgSym->GetDataSrc())
    {
    case DataSrcType::FOREX_TESTER:
        pel.SetupTechs(m_i, p, strat, techRect, d, dark);
        break;
    case DataSrcType::MONERO:
        pel.SetupTechsXform(p, simTS, techRect, d);
        break;
    case DataSrcType::GENERATED:
        pel.SetupTechsXform(p, simTS, techRect, d);
        break;
    }

    m_techLineCursor = new QCPGraph(techRect->axis(QCPAxis::atBottom), techRect->axis(QCPAxis::atLeft));
    m_techLineCursor->setPen(QPen(Qt::black));
    m_techLineCursor->setAntialiased(false);
    pel.SetPenGrey(m_dark, m_techLineCursor);
    p->addPlottable(m_techLineCursor);

        // interconnect x axis ranges of main and bottom axis rects:
    connect(p->xAxis, SIGNAL(rangeChanged(QCPRange)), techRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(techRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), p->xAxis, SLOT(setRange(QCPRange)));

    return techRect;
}
