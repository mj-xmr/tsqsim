/***************************************************************
 * Name:      FuzzyCarriageMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#include "wx_pch.h"
#include "FuzzyCarriageMain.h"

#ifndef WX_PRECOMP
//(*InternalHeaders(FuzzyCarriageFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include <wx/msgdlg.h>
#endif
#include "MyTimer.h"
#include "myScrolledWindow.h"

//(*IdInit(FuzzyCarriageFrame)
const long FuzzyCarriageFrame::ID_SCROLLEDWINDOW1 = wxNewId();
const long FuzzyCarriageFrame::ID_SLIDER1 = wxNewId();
const long FuzzyCarriageFrame::ID_SLIDER2 = wxNewId();
const long FuzzyCarriageFrame::ID_BUTTON1 = wxNewId();
const long FuzzyCarriageFrame::ID_BUTTON2 = wxNewId();
const long FuzzyCarriageFrame::ID_CHOICE1 = wxNewId();
const long FuzzyCarriageFrame::ID_CHECKBOX1 = wxNewId();
const long FuzzyCarriageFrame::ID_PANEL1 = wxNewId();
const long FuzzyCarriageFrame::idMenuQuit = wxNewId();
const long FuzzyCarriageFrame::idMenuAbout = wxNewId();
const long FuzzyCarriageFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FuzzyCarriageFrame,wxFrame)
    //(*EventTable(FuzzyCarriageFrame)
    //*)
END_EVENT_TABLE()

FuzzyCarriageFrame::FuzzyCarriageFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FuzzyCarriageFrame)
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, id, _("Controlling a carriage with a fuzzy controller"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(719,450));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(200,144), wxSize(616,450), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    m_scrWin = new myScrolledWindow(Panel1, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL, _T("ID_SCROLLEDWINDOW1"));
    BoxSizer2->Add(m_scrWin, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Position"));
    m_slPos = new wxSlider(Panel1, ID_SLIDER1, 0, -1000, 1000, wxDefaultPosition, wxDefaultSize, wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
    StaticBoxSizer1->Add(m_slPos, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Velocity"));
    m_slVel = new wxSlider(Panel1, ID_SLIDER2, 0, -1000, 1000, wxDefaultPosition, wxDefaultSize, wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER2"));
    StaticBoxSizer2->Add(m_slVel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Operation"));
    m_butStart = new wxButton(Panel1, ID_BUTTON1, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    m_butStart->SetToolTip(_("Start the animation and physics"));
    StaticBoxSizer3->Add(m_butStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_butStop = new wxButton(Panel1, ID_BUTTON2, _("Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_butStop->SetToolTip(_("Stop the animation and physics"));
    StaticBoxSizer3->Add(m_butStop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_choiceTime = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    m_choiceTime->Append(_("10"));
    m_choiceTime->SetSelection( m_choiceTime->Append(_("20")) );
    m_choiceTime->Append(_("30"));
    m_choiceTime->Append(_("40"));
    m_choiceTime->Append(_("50"));
    m_choiceTime->SetToolTip(_("Refresh rate in ms. Increase it if you\'re experiencing performance problems"));
    StaticBoxSizer3->Add(m_choiceTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_chkControl = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Fuzzy control"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_chkControl->SetValue(false);
    m_chkControl->SetToolTip(_("Enable fuzzy control to keep the carriage in position"));
    StaticBoxSizer3->Add(m_chkControl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->SetSizeHints(Panel1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_slPosCmdScrollChanged);
    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_slPosCmdScrollChanged);
    Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_slVelCmdScrollChanged);
    Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_slVelCmdScrollChanged);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_butStartClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_butStopClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&FuzzyCarriageFrame::Onm_chkControlClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FuzzyCarriageFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FuzzyCarriageFrame::OnAbout);
    //*)

    m_timer = new MyTimer(this, m_scrWin, m_carriage);
    m_timer->SetControl(m_chkControl->IsChecked());
}

FuzzyCarriageFrame::~FuzzyCarriageFrame()
{
    //(*Destroy(FuzzyCarriageFrame)
    //*)

  delete m_timer;
}

void FuzzyCarriageFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void FuzzyCarriageFrame::OnAbout(wxCommandEvent& event)
{
  wxString msg;
  msg << _T("Press start to enable animation and physics.\nIf you are experiencing performance problems, ") <<
  _T("increase the refresh rate using the listbox with number on it, indicating an amount of miliseconds") <<
  _T("per cycle, and press Start again.\n") <<
  _T("Use the sliders to put the carriage into a starting position.\n") <<
  _T("Use the Fuzzy control checkbox to bring the carriage into position.\n") <<
  _T("The sliders also let you impose disturbances after you ran the controller.\n\n") <<
  _T("Project's webpage:\nhttp://sourceforge.net/projects/libfuzzyengine") <<
  _T("\n\n(C) 2010 Szymon Ender\nLicence: GPL v3");
  wxMessageBox(msg, _("Welcome to Fuzzy Carriage"));
}

void FuzzyCarriageFrame::Onm_butStartClick(wxCommandEvent& event)
{
  long t;
  wxString sel = m_choiceTime->GetStringSelection();
  if (sel.ToLong(&t) )
  {
    m_timer->Start( t, wxTIMER_CONTINUOUS );
  }
  else
  {
    wxMessageBox(_T("Could not start timer = ") + sel , _("Errot"));
  }


}

void FuzzyCarriageFrame::Onm_butStopClick(wxCommandEvent& event)
{
  m_timer->Stop();
}

void FuzzyCarriageFrame::Onm_slVelCmdScrollChanged(wxScrollEvent& event)
{
  m_carriage.SetVel( event.GetSelection() / (double) m_slVel->GetMax() );
}

void FuzzyCarriageFrame::Onm_slPosCmdScrollChanged(wxScrollEvent& event)
{
  m_carriage.SetPos( event.GetSelection() / (double) m_slPos->GetMax() );
}

void FuzzyCarriageFrame::Onm_chkControlClick(wxCommandEvent& event)
{
  m_timer->SetControl(event.IsChecked());
}

void FuzzyCarriageFrame::SetSliderVel( double velPercent )
{
  m_slVel->SetValue( (int)(velPercent * m_slVel->GetMax()) );
}

void FuzzyCarriageFrame::SetSliderPos( double posPercent )
{
  m_slPos->SetValue( (int)(posPercent * m_slPos->GetMax()) );
}
