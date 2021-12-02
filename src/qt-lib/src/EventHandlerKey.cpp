#include "pch_qt.h"
#include "EventHandlerKey.h"
#include "MyMainWindow.h"
#include "Monster.h"
#include "FrameIter.h"




EventHandlerKey::EventHandlerKey(){}
EventHandlerKey::~EventHandlerKey(){}

extern bool cursorPlot;         /// TODO: extern is a code smell. Has to be wrapped in a stateful class and distributed along the project, where it's needed.
extern bool trendLinePlotStart;
extern bool trendLinePlotEnd;

void EventHandlerKey::keyPressEvent(MyMainWindow * win, QKeyEvent *event) const
{
    Monster mon;
    //cout << "ASD"<< endl;
    switch(event->key()) /// TODO: Print switchable help for keys (and mouse) on the corner of the screen. Take care of white/black theme
    {                    /// TODO: Print switchable help for mouse
    case Qt::Key_Escape:
        exit(0);
        break;
    case Qt::Key_Control:
        win->Reload(mon, false);
        break;
    case Qt::Key_C:
        win->m_i = win->m_iMouse;
        FrameIter().OnFrame(win);
        break;
    case Qt::Key_E:
        win->SetLabelStart(win->m_i);
        break;
    case Qt::Key_R:
        win->SetLabelEnd(win->m_i);
        break;
    case Qt::Key_F:
        win->SaveLabel();
        break;
    case Qt::Key_H: /// TODO: This should be H for Help.
        win->screenShot();
        break;
    case Qt::Key_Z:
        cursorPlot = not cursorPlot;
        win->UpdateCursor(win->m_x, win->m_y);
        break;
    case Qt::Key_X:
        win->UpdateCursor(win->m_x, win->m_y);
        cursorPlot = false;
        break;
    /*
    case Qt::Key_Q:
        trendLinePlotStart = not trendLinePlotStart;
        win->UpdateTrendLine(win->m_x, win->m_y, true);
        break;
    case Qt::Key_W:
        trendLinePlotEnd = not trendLinePlotEnd;
        win->UpdateTrendLine(win->m_x, win->m_y, false);
        break;
    */
    case Qt::Key_A:
        win->RegressionStart(win->m_iMouse);
        //FrameIter().OnFrame(win);
        break;
    case Qt::Key_D:
        win->RegressionEnd(win->m_iMouse);
        //FrameIter().OnFrame(win);
        break;
    case Qt::Key_G:
        win->RegressionMove(win->m_iMouse);
        //FrameIter().OnFrame(win);
        break;
    case Qt::Key_S:
        win->RegressionEndOpti(win->m_iMouse);
        //FrameIter().OnFrame(win);
        break;
    case Qt::Key_P:
        //win->RegressionStationarityPython();
        win->NovelityPython(win->m_iMouse);
        break;
    case Qt::Key_W:
        win->RegressionDegreeUp();
        break;
    case Qt::Key_Q:
        win->RegressionDegreeDown();
        break;
    case Qt::Key_M:
        win->DumpPeriod();
        break;
    case Qt::Key_B:
        win->Bet(win->m_iMouse);
        break;
    /*
    case Qt::Key_A:
        win->UpdateTrendLine(win->m_x, win->m_y, true);
        trendLinePlotStart = false;
        break;
    case Qt::Key_S:
        win->UpdateTrendLine(win->m_x, win->m_y, false);
        trendLinePlotEnd = false;
        break;
    */
    case Qt::Key_Insert:
        win->DeleteLabelStrat();
        break;
    case Qt::Key_Home:
        win->NewLabelStrat(true);
        break;
    case Qt::Key_End:
        win->NewLabelStrat(false);
        break;
    case Qt::Key_Space:
        win->StopTimer();
        FrameIter().OnFrame(win);
        break;
    case Qt::Key_Backspace:
        win->StopTimer();
        win->m_dirRight = false;
        FrameIter().OnFrame(win);
        win->m_dirRight = true;
        break;
    case Qt::Key_Delete:
        win->StopTimer();
        win->m_dirRight = false;
        break;
    case Qt::Key_PageDown:
        win->StopTimer();
        win->m_dirRight = true;
        break;
    case Qt::Key_Up:
        win->Reload(mon, false, +1, 2, 2);
        break;
    case Qt::Key_Down:
        win->Reload(mon, false, -1, 2, 2);
        break;
    case Qt::Key_Right:
        win->Reload(mon, false, 2, +1, 2);
        break;
    case Qt::Key_Left:
        win->Reload(mon, false, 2, -1, 2);
        break;
    case Qt::Key_BracketRight:
        win->Reload(mon, false, 2, 2, +1);
        break;
    case Qt::Key_BracketLeft:
        win->Reload(mon, false, 2, 2, -1);
        break;
    case Qt::Key_0:
        win->StartTimer(10);
        break;
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        win->StartTimer(event->key() - Qt::Key_0);
        break;
    default:
        break;
    }
}
