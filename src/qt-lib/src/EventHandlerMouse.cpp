#include "pch_qt.h"

#include "EventHandlerMouse.h"
#include "MyMainWindow.h"
#include "PlotDataBase.h"
#include "Monster.h"
#include "IPeriod.h"



using namespace std;

EventHandlerMouse::EventHandlerMouse(){}
EventHandlerMouse::~EventHandlerMouse(){}

bool cursorPlot = false;
bool trendLinePlotStart = false;
bool trendLinePlotEnd = false;

static unsigned tdiff = 0;
static unsigned tprev = 0;
void EventHandlerMouse::mouseMove(MyMainWindow * win, QMouseEvent *event) const
{
    try
    {
        if (win->m_training)
            return;
        win->m_x = event->pos().x();
        win->m_y = event->pos().y();

        unsigned diffNow = QDateTime::currentMSecsSinceEpoch() - tprev;
        if (diffNow > tdiff * 1.02)
        {
            tprev = QDateTime::currentMSecsSinceEpoch();
            if (cursorPlot)
                win->UpdateCursor(win->m_x, win->m_y);
            if (trendLinePlotStart)
                win->UpdateTrendLine(win->m_x, win->m_y, true);
            if (trendLinePlotEnd)
                win->UpdateTrendLine(win->m_x, win->m_y, false);

            tdiff = QDateTime::currentMSecsSinceEpoch() - tprev;
            //qDebug() << "refresh";
        }
        //qDebug() << "diffNow = " << diffNow << ", tdiff = " << tdiff;


        // Time of cursor:
        double coord = win->GetQCP()->xAxis->pixelToCoord(win->m_x);
        //const QVector<double> & time     = win->GetData().GetTime();
        const QVector<double> & timeOrig = win->GetData().GetTimeOrig();
        double t0 = timeOrig[0];

        QDateTime dt0;
        dt0.setTime_t(t0);

        uint64_t numMilis = win->GetPeriod().GetNumSeconds() * 1000;

        QDateTime dtNow;
        dtNow.setTime_t(coord);
        const qint64 msse = dtNow.toMSecsSinceEpoch();
        const qint64 msseScaledToPeriod = qint64(msse / numMilis) * numMilis;
        const qint64 msseScaledShifted = msseScaledToPeriod + numMilis / 2;
        //QDateTime dts;
        dtNow.setMSecsSinceEpoch(msseScaledShifted);
        const qint64 s20 = dt0.secsTo(dtNow);
        const int idx = s20 / win->GetPeriod().GetNumSeconds();

        win->m_iMouse = idx;

        /*
        double timeFakeAtCursor = timeOrig.at(idx);
        QDateTime dtFake;
        dtFake.setTime_t(timeFakeAtCursor);
        qDebug() << idx << ", m_x = " << dtFake.toString() << ", coordSecs = " << dtNow.toString();
        */
    }
    catch (std::exception & ex)
    {
        qDebug() << "Exception at EventHandlerMouse::mouseMove() = " << ex.what();
    }
}

void EventHandlerMouse::mousePress(MyMainWindow * win, QMouseEvent *event) const
{
    if (event->button() == Qt::LeftButton)
    {
        win->GetQCP()->m_delayed = true;
        event->accept();
    }
    else
    if (event->button() == Qt::RightButton)
    {
        Monster mons;
        //win->Reload(false); // Left to Control
        win->Reload(mons, false, 2, 2, 2); // Don't touch the relative shifts
        event->accept();
    }
};

void EventHandlerMouse::mouseRelease(MyMainWindow * win, QMouseEvent *event) const
{
    if (event->button() == Qt::LeftButton)
    {
        event->accept();
        win->GetQCP()->m_delayed = false;
    }
};
