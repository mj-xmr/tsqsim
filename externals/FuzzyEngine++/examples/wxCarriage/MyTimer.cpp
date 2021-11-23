#include "wx_pch.h"

#ifndef WX_PRECOMP
	#include <wx/msgdlg.h>
#endif
#include "MyTimer.h"
#include "myScrolledWindow.h"
#include "FuzzyCarriageMain.h"

MyTimer::MyTimer( FuzzyCarriageFrame * frame, myScrolledWindow * scrWin, Carriage & carriage)
:
m_frame(frame),
m_scrWin(scrWin),
m_carriage(carriage)
{

}

void MyTimer::SetControl( bool control )
{
  m_control = control;
}

void MyTimer::Notify()
{
  double force = 0;
  if ( m_control )
  {
    try
    {
      fuzzyController.SetInputPosition( m_carriage.GetPos() );
      fuzzyController.SetInputVelocity( m_carriage.GetVel() );

      fuzzyController.Evaluate();
      force = fuzzyController.GetOutputForce();
      fuzzyController.Reset();
      // wxPuts(wxString::Format(_T("%.3f"), force)) ;
    }
    catch ( exception & e )
    {
      wxMessageBox( wxString::FromAscii(e.what()), _T("Exception caught in MyTimer::Notify()"));
    }
  }
  m_carriage.Run( GetInterval(),  force);
  m_scrWin->UpdateCarriage(m_carriage, force);
  m_scrWin->Refresh();

  m_frame->SetSliderPos(m_carriage.GetPosPercent());
  m_frame->SetSliderVel(m_carriage.GetVelPercent());

}
