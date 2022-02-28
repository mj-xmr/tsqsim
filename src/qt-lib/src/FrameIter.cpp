#include "pch_qt.h"
#include "MyMainWindow.h"
#include "FrameIter.h"
#include "Util.h"
#include "PlotDataBase.h"
#include <IPeriod.h>
#include <IStrategy.h>
#include "ConfigGlob.h"
#include "MaPeriods.h"
//#include "StopLossController.h"
#include "IBufferCandles.h"
//#include <ISimulatorStd.h>
#include "ISimulator.h"
//#include "IPosition.h"
#include "StateFactory.h"
#include <Template/Array.hpp>
#include <Template/CorradePointer.h>

#include <Ios/Osstream.hpp>


using namespace std;

FrameIter::FrameIter(){}
FrameIter::~FrameIter(){}




static void PrintCandle(const IStrategy & strat, int i)
{
    //static int j = 0;
    //cout << "const Candle c" << strat->GetPeriod().GetCandles()[i].PrintOCHL() << endl;
    //cout << "vc.push_back(Candle" << strat->GetPeriod().GetCandles()[i].PrintOCHL() << "); "  << j++ << endl;
    //return "Candle = " + strat.GetPeriod().GetCandles()[i].PrintOCHL();
    //cout << strat.GetPeriod().GetCandles()[i].GetDate() << endl;
    //cout << "Candle = " << strat.GetPeriod().GetCandles()[i].GetDateStr() << endl;
}

void FrameIter::OnFrameReact(MyMainWindow * win, int i) const
{
    //gcfg.USE_CACHE = false;
    const PlotDataBase & d = win->GetData();
    const int sz = d.GetSz();

    const int j = Util::CalcIdx(i, sz);
    Direction dir = gcfg.DIRECTION;
    //dir = BUY;
    const State st = *StateFactory().Create(dir, j);
    const State stBull = *StateFactory().Create(BUY, j);
    const State stBear = *StateFactory().Create(SELL, j);

    const QString symPerName = Util::FormatSymPer(win->GetSymbol(), win->GetPeriod().GetName().str());

    if (j >= win->GetStrategy().Len())
    {
        win->GetQCP()->replot();
        win->setWindowTitle(symPerName + "; " + "Strategy too short");
        return; // Strategy would crash
    }

    win->GetQCP()->replot();
    EnjoLib::Osstream oss;

    oss << Util::GetIndexes(d, win->m_i) << ", Now = " << Util::DateToStr(d.GetTimeOrig()[i]).toUtf8().constData();
    //cout << oss.str();
    //oss << ", MaSlow = " << win->GetStrategy().GetMaPeriods(st).m_maSlow << endl;

    //cout << "Now = " << d.datesStr[i].toUtf8().constData() << endl;


    win->setWindowTitle(symPerName + "; " + oss.str().c_str());
    // Print candle
    PrintCandle(win->GetStrategy(), j);
    //if (m_strategy->IsSignal(*StateFactory().Create(BUY, st.i)) || m_strategy->IsSignal(*StateFactory().Create(SELL, st.i))) {PrintCandle(m_strategy.get(), st.i);}
#ifdef DEBUG
    /// TODO: Reenable
    win->m_mons.m_simulatorGeneric->Iter(st.i, &dir); // For a single direction debugging
    //m_simulator->Iter(st.i); // For a bigger picture debugging (SL and TP)
#else
    /// TODO: Reenable
    // win->m_mons.m_simulator->Iter(j); // For a bigger picture debugging (SL and TP)
    win->m_mons.m_simulatorGeneric->Iter(j);
#endif

    //PatRounding patRounding(m_symbol->GetPeriod(m_periodName));
    //patRounding.IsSignal(*StateFactory().Create(BUY, st.i));

#ifdef DEBUG
    //float slBull = m_simulator->GetSL(stBull);
    //m_slBull->setData(d.GetTime(), QVector<double>(d.GetTime().size(), slBull));
    //float slBear = m_simulator->GetSL(stBear);
    //m_slBear->setData(d.GetTime(), QVector<double>(d.GetTime().size(), slBear));
#else
/// TODO: Reenable
/*
    StopLossController slCtrl(win->GetStrategy());
    const float vol     = win->m_mons.m_simulator->GetPosition().GetVolume();
    const float spread  = win->GetStrategy().GetDataProvider().GetSpread(stBull.i);
    float slBull = slCtrl.GetSL(stBull,  win->GetStrategy(), vol, spread);
    float slBear = slCtrl.GetSL(stBear, win->GetStrategy(), vol, spread);
    //float slBull = win->m_simulator->GetSL(stBull);
    //float slBear = win->m_simulator->GetSL(stBear);
    //float slBear = m_simulator->GetSL(stBear);
    win->m_slBull->setData(d.GetTime(), QVector<double>(sz, slBull)); /// TODO: to moglaby byc linia po prostu
    win->m_slBear->setData(d.GetTime(), QVector<double>(sz, slBear));
*/
#endif
    win->GetQCP()->replot();
}

void FrameIter::OnFrame(MyMainWindow * win) const
{
    const PlotDataBase & d = win->GetData();
    const unsigned sz = d.GetSz();
    if (win->m_i >= sz)
    {
        --win->m_i;
        return;
    }

    const unsigned i = win->m_dirRight ? win->m_i++ : win->m_i--;


    if (win->m_dirRight)
        win->m_candlesticks->addData(d.GetFinancial().at(i));
    else
        win->m_candlesticks->removeData(d.GetFinancial().at(i).key);


    OnFrameReact(win, i);
}
