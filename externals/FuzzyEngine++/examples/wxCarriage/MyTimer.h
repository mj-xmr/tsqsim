/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef MYTIMER_INCLUDED
#define MYTIMER_INCLUDED

#ifndef WX_PRECOMP
  #include <wx/timer.h>
#endif

#include "FuzzyController.hpp"
#include "Carriage.h"

class myScrolledWindow;
class FuzzyCarriageFrame;

class MyTimer : public wxTimer
{
  public:
    MyTimer( FuzzyCarriageFrame * frame, myScrolledWindow * scrWin, Carriage & carriage);
    void Notify();
    void SetControl( bool control );
  protected:

  private:
    FuzzyCarriageFrame * m_frame;
    myScrolledWindow * m_scrWin;
    Carriage & m_carriage;

    bool m_control;
    FuzzyController fuzzyController;

};

#endif // MYTIMER_INCLUDED
