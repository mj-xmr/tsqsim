#include "pch_qt.h"

#include "ui_mainwindow.h"
#include "MyMainWindow.h"
#include "EventHandlerKey.h"
#include "EventHandlerMouse.h"
#include "FrameIter.h"
//#include "PeriodUtil.h"

//#include "RegressionPrepare.h"
#include <ConfigMan.h>
#include <ConfigGlob.h>
#include <ConfigDirs.h>
//#include <IMainTester.h>
#include <Candle.h>

#include <IPeriod.h>
#include <ISymbol.h>
#include <IStrategy.h>
#include "PlotDataBase.h"
#include "LabelQT.h"
#include "LabelQTSignal.h"
#include "LabelsUtil.h"
#include "Util.h"
//#include "RegressionStationarity.h"
//#include "NovelityFactory.h"
//#include "BetIter.h"
//#include "SymbolFactory.h"
#include "IBufferCandles.h"
#include "Monster.h"
//#include <ISimulatorStd.h>

#include <EnjoLibBoost/Filesystem.hpp>
#include <Util/CharManipulationsTpl.hpp>
#include <Util/ProtocolCreatorFile.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Ios/Ofstream.hpp>

using namespace std;
using namespace EnjoLib;

MyMainWindow::MyMainWindow(QWidget *parent)
    : MainWindow(parent)
{
}

MyMainWindow::~MyMainWindow()
{
    StopTimer();
}

void MyMainWindow::UpdateTrendLine(double xx, double yy, bool start)
{
    QCustomPlot *customPlot=ui->customPlot;
    double x=customPlot->xAxis->pixelToCoord(xx);
    double y=customPlot->yAxis->pixelToCoord(yy);

    if (start)
        m_trendLine->start->setCoords(x, y);
    else
        m_trendLine->end->setCoords(x, y);
    customPlot->replot();
}

void MyMainWindow::UpdateCursor(double xx, double yy)
{
    QCustomPlot *customPlot=ui->customPlot;
    double x=customPlot->xAxis->pixelToCoord(xx);
    double y=customPlot->yAxis->pixelToCoord(yy);

    m_hCursor->start->setCoords(QCPRange::minRange, y);
    m_hCursor->end->setCoords(QCPRange::maxRange, y);

    m_vCursor->start->setCoords(x, QCPRange::minRange);
    m_vCursor->end->setCoords(x, QCPRange::maxRange);

    if (m_techLineCursor)
    {
        m_techLineCursor->clearData();
        m_techLineCursor->addData(x, 0);
        m_techLineCursor->addData(x, 100);
    }

    const int sti = m_mons.m_symbol->GetPeriod(m_mons.m_periodName).GetCandles().ConvertIndex(m_iMouse);
    EnjoLib::Osstream oss;
    oss << "         " << y << " " << sti << "\n";
    m_txtPrice->position->setCoords(x, y); // place position at center/top of axis rect
    m_txtPrice->setText(oss.str().c_str());
    //QString symPerName = Util::FormatSymPer(GetSymbol(), GetPeriod().GetName());
    //setWindowTitle(symPerName + "; " + oss.str().c_str());

    //double yt = m_techRect->axis(QCPAxis::atTop)->pixelToCoord((735-yy));
    //m_techLineCursor->addData(QCPRange::minRange, yt);
    //m_techLineCursor->addData(QCPRange::maxRange, yt);
    //vCursor = new QCPItemLine(customPlot->plotLayout()->elementAt(1));
    //qDebug() << xx << " " << yy << " " << yt << ", y = " << y;
    customPlot->replot();
}

void MyMainWindow::RegressionStart(int i)
{
    m_mons.reg.past = CalcIdxMon(i);
    //system("clear");
    //const IPeriod & per = m_symbol->GetPeriod(m_mons.m_periodName);
    //RegressionOpti(true).GetLaterOpti(per, gcfg.DIRECTION, reg.future, reg.degree, 0, reg.past);
    RegressionPlot(false);
}

void MyMainWindow::RegressionEnd(int i)
{
    m_mons.reg.future = CalcIdxMon(i);
    //reg.past = reg.future + 50;
    //const IPeriod & per = m_symbol->GetPeriod(m_mons.m_periodName);
    //RegressionOpti(true).GetLaterOpti(per, gcfg.DIRECTION, reg.future, reg.degree, 0, reg.past);
    RegressionPlot(false);
}

void MyMainWindow::RegressionMove(int i)
{
    const int diff = CalcIdxMon(i) - m_mons.reg.future;
    m_mons.reg.past += diff;
    m_mons.reg.future += diff;
    RegressionPlot(false);
}

void MyMainWindow::RegressionEndOpti(int i)
{
    m_mons.reg.future = CalcIdxMon(i);
    RegressionPlot(true);
}
        //GetLaterOpti
void MyMainWindow::RegressionPlot(bool opti)
{
    try
    {
        const IPeriod & per = m_mons.m_symbol->GetPeriod(m_mons.m_periodName);
        const PlotDataBase & d = *m_mons.m_d;

        //LOGL << "Reg Start End = " << reg.past << ", " << reg.future << Endl;
        //LOGL << "Reg diff = " << abs(reg.past - reg.future) - gcfg.REGRESS_MIN_SAMPLES << Endl;
        for (QCPAbstractItem * line : m_regressLineUser) {LOGL << ""; ui->customPlot->removeItem(line);} m_regressLineUser.clear();
        /// TODO: Restore
        //m_regressLineUser = RegressionPrepare().Prep(ui->customPlot, per, m_mons.m_strategy.get(), d, opti, m_mons.reg);
        ui->customPlot->replot();
    }
    catch (exception & ex)
    {
        Util::HandleException(ex);
    }
}

void MyMainWindow::RegressionStationarityPython()
{
    /// TODO: restore
    //RegressionStationarity(m_mons.m_symbol->GetPeriod(m_mons.m_periodName)).RunScript();
}
void MyMainWindow::NovelityPython(int i)
{
    /// TODO: restore
    const int sti = CalcIdxMon(i);
    //LOGL << "sti = " << sti << Endl;
    //NovelityType novType = NOVELITY;
    //NovelityType novType = NOVELITY_STDDEV;
    //const auto nov = NovelityFactory().Create(m_mons.m_symbol->GetPeriod(m_mons.m_periodName), novType);
    //nov->Plot(sti);
}

void MyMainWindow::Bet(int i)
{
    /// TODO: restore LATER
    /*
    int sti = CalcIdxMon(i) - 1;
    const Candle & canCurr = m_mons.m_symbol->GetPeriod(m_mons.m_periodName).GetCandles()[sti];
    const Candle & canPrev = m_mons.m_symbol->GetPeriod(m_mons.m_periodName).GetCandles()[sti+1];
    //const double changeAvg = m_simulatorBet->GetChangeAverage(canCurr.GetHour());
    const double changeAvg = 0;
    //const BetIter betIter(changeAvg, m_simulatorBet->GetChangeAverageMean());
    const BetIter betIter(changeAvg, changeAvg);

    const double coordy = GetQCP()->yAxis->pixelToCoord(m_y);

    const double procChange = (coordy - canPrev.GetClose()) / canPrev.GetClose();

    const double houseProfit = betIter.GetHouseProfitSpecifyBet(procChange);
    LOGL << "bet sti = " << coordy << ", Profit = " << houseProfit << Endl;
    */
}

void MyMainWindow::RegressionDegreeUp()
{
    const int maxDegree = 30;
    m_mons.reg.degree++;
    if (m_mons.reg.degree > maxDegree)
    {
        m_mons.reg.degree = maxDegree;
    }
    LOGL << "Reg degree = " << m_mons.reg.degree << Endl;
    RegressionPlot(false);
}
void MyMainWindow::RegressionDegreeDown()
{
    const int minDegree = 1;
    m_mons.reg.degree--;
    if (m_mons.reg.degree < minDegree)
    {
        m_mons.reg.degree = minDegree;
    }
    LOGL << "Reg degree = " << m_mons.reg.degree << Endl;
    RegressionPlot(false);
}


void MyMainWindow::timerEvent(QTimerEvent *event)
{
    FrameIter().OnFrame(this);
}

void MyMainWindow::StartTimer(int speed)
{
    StopTimer();
    if (!timerId)
        timerId = startTimer(1000 / speed / speed);
}
void MyMainWindow::StopTimer()
{
    if (timerId)
        killTimer(timerId);
    timerId = 0;
}

void MyMainWindow::SetLabelStart(int i)
{
    const double t = m_mons.m_d->GetTimeOrig()[i];
    const EnjoLib::Str dateTimeStr = Util::DateToDateIntStr(t);
    EnjoLib::CharManipulationsTpl cm;
    const DateInt YYYYMMDDhhmmss = cm.ToNumber<uint64_t>(dateTimeStr);
    m_mons.m_labelQT->SetStart(YYYYMMDDhhmmss);
    qDebug() << (m_mons.m_labelQT->IsValid() ? "+ " : "  ") << "Label Start " << Util::DateToStr(t) << " " << YYYYMMDDhhmmss;
}

void MyMainWindow::SetLabelEnd(int i)
{
    const double t = m_mons.m_d->GetTimeOrig()[i];
    const EnjoLib::Str dateTimeStr = Util::DateToDateIntStr(t);
    EnjoLib::CharManipulationsTpl cm;
    const DateInt YYYYMMDDhhmmss = cm.ToNumber<uint64_t>(dateTimeStr);
    m_mons.m_labelQT->SetEnd(YYYYMMDDhhmmss);
    qDebug() << (m_mons.m_labelQT->IsValid() ? "+ " : "  ") << "Label End   " << Util::DateToStr(t) << " " << YYYYMMDDhhmmss;
    //qDebug() << QString(m_labelQT->ToString().c_str());
}

void MyMainWindow::SaveLabel()
{
    using namespace EnjoLib;
    //qDebug() << QString(m_labelQT->ToString().c_str());
    if (m_mons.m_labelQT->IsValid())
    {
        const Str dir = LabelsUtil::GetLabelRangeDir(GetStrategy());
        Filesystem().CreateDirIfNotExists(dir.str());

        Ofstream labelsFile(LabelsUtil::GetLabelRangePath(GetStrategy()).c_str(), true, true);
        qDebug() << "Saving: " << m_mons.m_labelQT->ToString().c_str();
        labelsFile << m_mons.m_labelQT->ToString() << '\n';
    }
    else
    {
        qDebug() << QString(m_mons.m_labelQT->ToString().c_str());
    }
}

void MyMainWindow::NewLabelStrat(bool bullish)
{
    using namespace EnjoLib;
    if (m_training)
    {
        const State st = m_sigStatesTraining.at(m_iTraining-1); // was incremented
        //qDebug() << st.i;
        m_trainingStatesAccepted.push_back(st);
        Monster monster;
        Reload(monster, 3);
        return;
    }

    //const double t = m_d->GetTimeOrig()[m_i - 1];
    const double t = m_mons.m_d->GetTimeOrig()[m_i + 1];
    const EnjoLib::Str dateTimeStr = Util::DateToDateIntStr(t);
    EnjoLib::CharManipulationsTpl cm;
    const DateInt YYYYMMDDhhmmss = cm.ToNumber<uint64_t>(dateTimeStr);

    LabelQTSignal lab(GetPeriod(), GetStrategy(), YYYYMMDDhhmmss, Direction(bullish));
    Filesystem().CreateDirIfNotExists(LabelsUtil::GetLabelSignalDir(GetStrategy()).c_str());
    Ofstream labelsFile(LabelsUtil::GetLabelSignalPath(GetStrategy()).c_str(), true, true);
    qDebug() << "Saving: " << lab.ToString().c_str();
    labelsFile << lab.ToString() << '\n';

}
void MyMainWindow::DeleteLabelStrat()
{
     qDebug() << "DeleteLabelStrat(): Unimplemented";
}

void MyMainWindow::DumpPeriod()
{
    /// TODO: Restore
    /*
    ELO
    EnjoLib::ProtocolCreatorFile ofile(ConfigDirs().DIR_DATA + "periodDump.txt");
    const EnjoLib::Str & perData = PeriodUtil().Data2Str(GetPeriod());
    LOG << "Saving period data to: " << ofile.GetFileName() << Endl;
    ofile.AddStr(perData);

    LOG << "PeriodData:\n" << perData << Endl;
    LOG << "\nSaved period data to: " << ofile.GetFileName() << Endl;
    */
}

int MyMainWindow::CalcIdxMon(int i) const
{
    return Util::CalcIdx(i, m_mons.m_d->GetSz());
}

QCustomPlot * MyMainWindow::GetQCP()
{
    return ui->customPlot;
}
const PlotDataBase & MyMainWindow::GetData() const
{
    return *m_mons.m_d;
}
const IPeriod & MyMainWindow::GetPeriod() const
{
    return m_mons.m_symbol->GetPeriod(m_mons.m_periodName);
}
const IStrategy & MyMainWindow::GetStrategy() const
{
    return *m_mons.m_strategy;
}
const ISymbol & MyMainWindow::GetSymbol() const
{
    return *m_mons.m_symbol;
}

void MyMainWindow::mouseMove(QMouseEvent *event)
{
    EventHandlerMouse().mouseMove(this, event);
}

void MyMainWindow::mousePress(QMouseEvent *event)
{
    EventHandlerMouse().mousePress(this, event);
};

void MyMainWindow::mouseRelease(QMouseEvent *event)
{
    EventHandlerMouse().mouseRelease(this, event);
};

void MyMainWindow::keyPressEvent(QKeyEvent *event)
{
    EventHandlerKey().keyPressEvent(this, event);
}
