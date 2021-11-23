/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/
#include "wx_pch.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Carriage.h"
#include "myScrolledWindow.h"


BEGIN_EVENT_TABLE(myScrolledWindow, wxScrolledWindow)

   // EVT_MOTION(myScrolledWindow::OnMouseMove)
   // EVT_LEFT_UP(myScrolledWindow::OnLeftUp)
END_EVENT_TABLE()

// myScrolledWindow dziedziczy z wxScrolledWindow
myScrolledWindow::myScrolledWindow(wxWindow * parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style , const wxString& name):
  wxScrolledWindow((wxWindow*)parent, id, pos, size, style, name)
{
  bgCol.Set(230,240,255);
  SetBackgroundColour (bgCol);
SetBackgroundStyle(wxBG_STYLE_PAINT);

  //ScrollbarsOn(GetSize());
  //Connect(wxID_ANY,wxEVT_SIZE,wxSizeEventHandler(myScrolledWindow::OnSize));
}

myScrolledWindow::~myScrolledWindow()
{
}

void myScrolledWindow::OnDraw (wxDC& dcNormal)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBrush(bgCol);
    dc.DrawRectangle(GetClientSize());

    const int pixInMeter = 150;
  const int pixInNewton = 30;
  int w = 30;
  int h = 20;
  int r = 5;

  int centerX = GetClientSize().GetWidth() / 2;
  int centerY = GetClientSize().GetHeight() / 2;

  int bottom = centerY + h + r;
  int top = centerY - h;

  dc.DrawLine(centerX , top , centerX, bottom);
  dc.DrawLine(centerX - pixInMeter , top, centerX - pixInMeter, bottom);
  dc.DrawLine(centerX + pixInMeter , top, centerX + pixInMeter, bottom);
  dc.DrawLine(centerX - pixInMeter * 2 - w/2 , top, centerX - pixInMeter * 2 - w/2, bottom);
  dc.DrawLine(centerX + pixInMeter * 2 + w/2 , top, centerX + pixInMeter * 2 + w/2, bottom);

  dc.DrawText(wxString::Format(_T("%d m"),0), centerX, bottom);
  dc.DrawText(wxString::Format(_T("%d m"),-1), centerX - pixInMeter, bottom);
  dc.DrawText(wxString::Format(_T("%d m"),1), centerX + pixInMeter, bottom);
  dc.DrawText(wxString::Format(_T("%d m"),-2), centerX - pixInMeter * 2 - w/2, bottom);
  dc.DrawText(wxString::Format(_T("%d m"),2), centerX + pixInMeter * 2 + w/2, bottom);

  int xCarriage = centerX + m_carriage.GetPos() * pixInMeter - w/2;
  dc.DrawRectangle( xCarriage, centerY, w, h);

  dc.DrawCircle(xCarriage + r, centerY + h, r);
  dc.DrawCircle(xCarriage - r + w - 1 , centerY + h, r);
  dc.DrawLine(0 , bottom, GetClientSize().GetWidth(),  bottom);

  int wForce = m_force * pixInNewton;
  int x1Force = xCarriage + (m_force > 0 ? w : 0);
  int x2Force = x1Force + wForce;
  dc.SetPen( *wxRED_PEN );
  dc.DrawLine( x1Force, centerY,  x2Force, centerY);

  dc.SetTextForeground( *wxRED );
  dc.DrawText(wxString::Format(_T("F = %.3f N"),m_force ), xCarriage - w, centerY - w);
}

void myScrolledWindow::UpdateCarriage( const Carriage & carriage, double force )
{
    m_carriage = carriage;
    m_force = force;
}



