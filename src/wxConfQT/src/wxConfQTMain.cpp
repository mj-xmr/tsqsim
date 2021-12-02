/***************************************************************
 * Name:      wxConfQTMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2015-08-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include <wx/valnum.h>
#include "wxConfQTMain.h"

#include "MyChoiceEnum.h"

using namespace std;

void wxConfQTFrame::Onm_choiceYearStartSelect(wxCommandEvent& event)
{
    if (m_chkYearsTogether->GetValue())
        m_choiceYearEnd->SetSelection(m_choiceYearStart->GetSelection());
    GeneralHandler();
}

void wxConfQTFrame::Onm_sliderBarsCmdScrollThumbRelease(wxScrollEvent& event)
{
    GeneralHandler();
}

void wxConfQTFrame::Onm_butLoadClick(wxCommandEvent& event)
{
    Read();
}


void wxConfQTFrame::On_General(wxCommandEvent& event)
{
    GeneralHandler();
}

void wxConfQTFrame::OnTF()
{
    ReadSelections();
    m_confTF.Write();
    m_confSym.Write();
}

void wxConfQTFrame::On_TF(wxCommandEvent& event)
{
    OnTF();
}

void wxConfQTFrame::On_QT(wxCommandEvent& event)
{
    ReadSelections();
    m_confQT.Write();
}

//(*InternalHeaders(wxConfQTFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxConfQTFrame)
const long wxConfQTFrame::ID_CHOICE7 = wxNewId();
const long wxConfQTFrame::ID_CHOICE13 = wxNewId();
const long wxConfQTFrame::ID_CHOICE1 = wxNewId();
const long wxConfQTFrame::ID_CHOICE2 = wxNewId();
const long wxConfQTFrame::ID_CHOICE3 = wxNewId();
const long wxConfQTFrame::ID_CHOICE4 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX1 = wxNewId();
const long wxConfQTFrame::ID_CHOICE5 = wxNewId();
const long wxConfQTFrame::ID_CHOICE6 = wxNewId();
const long wxConfQTFrame::ID_SLIDER1 = wxNewId();
const long wxConfQTFrame::ID_TEXTCTRL1 = wxNewId();
const long wxConfQTFrame::ID_BUTTON5 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX13 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX2 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX3 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX7 = wxNewId();
const long wxConfQTFrame::ID_BUTTON6 = wxNewId();
const long wxConfQTFrame::ID_CHOICE9 = wxNewId();
const long wxConfQTFrame::ID_CHOICE10 = wxNewId();
const long wxConfQTFrame::ID_CHOICE11 = wxNewId();
const long wxConfQTFrame::ID_CHOICE12 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX11 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX6 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX4 = wxNewId();
const long wxConfQTFrame::ID_BUTTON8 = wxNewId();
const long wxConfQTFrame::ID_BUTTON7 = wxNewId();
const long wxConfQTFrame::ID_BUTTON9 = wxNewId();
const long wxConfQTFrame::ID_BUTTON10 = wxNewId();
const long wxConfQTFrame::ID_BUTTON3 = wxNewId();
const long wxConfQTFrame::ID_TEXTCTRL2 = wxNewId();
const long wxConfQTFrame::ID_BUTTON4 = wxNewId();
const long wxConfQTFrame::ID_CHOICE8 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX5 = wxNewId();
const long wxConfQTFrame::ID_CHECKBOX8 = wxNewId();
const long wxConfQTFrame::ID_BUTTON2 = wxNewId();
const long wxConfQTFrame::ID_BUTTON1 = wxNewId();
const long wxConfQTFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxConfQTFrame,wxFrame)
    //(*EventTable(wxConfQTFrame)
    //*)
END_EVENT_TABLE()

wxConfQTFrame::wxConfQTFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxConfQTFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer6;

    Create(parent, wxID_ANY, _("Conf"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    Move(wxPoint(0,1000));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    m_choiceStrat = new MyChoiceEnum(this, ID_CHOICE7, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
    m_choiceStrat->SetSelection( m_choiceStrat->Append(_("DIV")) );
    BoxSizer2->Add(m_choiceStrat, 0, wxALL|wxEXPAND, 5);
    m_choiceDataSrc = new MyChoiceEnum(this, ID_CHOICE13, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE13"));
    m_choiceDataSrc->SetSelection( m_choiceDataSrc->Append(_("FX")) );
    m_choiceDataSrc->Append(_("Monero"));
    BoxSizer2->Add(m_choiceDataSrc, 0, wxALL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    m_choiceSym = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(125,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    m_choiceSym->Append(_("SPYUSDASD"));
    m_choiceSym->SetToolTip(_("Name of time series"));
    BoxSizer3->Add(m_choiceSym, 0, wxALL|wxEXPAND, 5);
    m_choicePeriod = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    m_choicePeriod->Append(_("m1"));
    m_choicePeriod->Append(_("m5"));
    m_choicePeriod->Append(_("m15"));
    m_choicePeriod->Append(_("m30"));
    m_choicePeriod->SetSelection( m_choicePeriod->Append(_("h1")) );
    m_choicePeriod->Append(_("h2"));
    m_choicePeriod->Append(_("h4"));
    m_choicePeriod->Append(_("h8"));
    m_choicePeriod->Append(_("h12"));
    m_choicePeriod->Append(_("d"));
    m_choicePeriod->SetToolTip(_("Name of discrete period"));
    BoxSizer3->Add(m_choicePeriod, 0, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxEXPAND, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Years"));
    m_choiceYearStart = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    m_choiceYearStart->SetSelection( m_choiceYearStart->Append(_("2001")) );
    StaticBoxSizer1->Add(m_choiceYearStart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_choiceYearEnd = new wxChoice(this, ID_CHOICE4, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    m_choiceYearEnd->SetSelection( m_choiceYearEnd->Append(_("2001")) );
    StaticBoxSizer1->Add(m_choiceYearEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_chkYearsTogether = new wxCheckBox(this, ID_CHECKBOX1, _("Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_chkYearsTogether->SetValue(true);
    m_chkYearsTogether->SetToolTip(_("Change years together"));
    StaticBoxSizer1->Add(m_chkYearsTogether, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer1, 1, wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Months"));
    m_choiceMonthStart = new wxChoice(this, ID_CHOICE5, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    m_choiceMonthStart->SetSelection( m_choiceMonthStart->Append(_("1")) );
    StaticBoxSizer2->Add(m_choiceMonthStart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_choiceMonthEnd = new wxChoice(this, ID_CHOICE6, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
    m_choiceMonthEnd->SetSelection( m_choiceMonthEnd->Append(_("1")) );
    StaticBoxSizer2->Add(m_choiceMonthEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer2, 1, wxEXPAND, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("% bars"));
    m_sliderBars = new wxSlider(this, ID_SLIDER1, 100, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    m_sliderBars->Hide();
    StaticBoxSizer3->Add(m_sliderBars, 0, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(StaticBoxSizer3, 0, wxEXPAND, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bar"));
    m_txtBar = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<long int>(&m_confSym.barNum), _T("ID_TEXTCTRL1"));
    StaticBoxSizer4->Add(m_txtBar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_butClearBar = new wxButton(this, ID_BUTTON5, _("Clr"), wxDefaultPosition, wxSize(35,-1), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticBoxSizer4->Add(m_butClearBar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_chkCache = new wxCheckBox(this, ID_CHECKBOX13, _("Che"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
    m_chkCache->SetValue(true);
    m_chkCache->SetToolTip(_("Use cache"));
    StaticBoxSizer4->Add(m_chkCache, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer4, 0, wxEXPAND, 5);
    m_sizerQT = new wxStaticBoxSizer(wxVERTICAL, this, _("QT"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    m_checkBigScreen = new wxCheckBox(this, ID_CHECKBOX2, _("BS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    m_checkBigScreen->SetValue(false);
    m_checkBigScreen->SetToolTip(_("Big screen"));
    BoxSizer8->Add(m_checkBigScreen, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_checkDirection = new wxCheckBox(this, ID_CHECKBOX3, _("Dir"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    m_checkDirection->SetValue(false);
    m_checkDirection->SetToolTip(_("Direction (BUY/SELL)"));
    BoxSizer8->Add(m_checkDirection, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_ckeckPltQT = new wxCheckBox(this, ID_CHECKBOX7, _("Plt"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    m_ckeckPltQT->SetValue(false);
    m_ckeckPltQT->SetToolTip(_("Plot screenshots with QT app"));
    m_ckeckPltQT->SetHelpText(_("Plot screenshots with QT app"));
    BoxSizer8->Add(m_ckeckPltQT, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_butPlotDialog = new wxButton(this, ID_BUTTON6, _("Plt"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    m_butPlotDialog->SetToolTip(_("Plots dialog"));
    BoxSizer8->Add(m_butPlotDialog, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_sizerQT->Add(BoxSizer8, 1, wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    m_choiceBuf1 = new MyChoiceEnum(this, ID_CHOICE9, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE9"));
    m_choiceBuf1->Append(_("1234567890"));
    m_choiceBuf1->SetForegroundColour(wxColour(49,22,242));
    BoxSizer9->Add(m_choiceBuf1, 0, wxALL|wxEXPAND, 5);
    m_choiceBuf2 = new MyChoiceEnum(this, ID_CHOICE10, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE10"));
    m_choiceBuf2->Append(_("1234567890"));
    m_choiceBuf2->SetForegroundColour(wxColour(9,125,10));
    BoxSizer9->Add(m_choiceBuf2, 0, wxALL|wxEXPAND, 5);
    m_sizerQT->Add(BoxSizer9, 1, wxEXPAND, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    m_choiceBuf3 = new MyChoiceEnum(this, ID_CHOICE11, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE11"));
    m_choiceBuf3->Append(_("asd"));
    m_choiceBuf3->SetForegroundColour(wxColour(200,8,39));
    BoxSizer11->Add(m_choiceBuf3, 0, wxALL|wxEXPAND, 5);
    m_choiceBufRainbow = new MyChoiceEnum(this, ID_CHOICE12, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE12"));
    m_choiceBufRainbow->Append(_("asd"));
    m_choiceBufRainbow->SetForegroundColour(wxColour(209,159,28));
    m_choiceBufRainbow->SetToolTip(_("Buf Rainbow"));
    BoxSizer11->Add(m_choiceBufRainbow, 0, wxALL|wxEXPAND, 5);
    m_sizerQT->Add(BoxSizer11, 1, wxEXPAND, 5);
    BoxSizer1->Add(m_sizerQT, 0, wxEXPAND, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("TF"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    m_checkIndivSym = new wxCheckBox(this, ID_CHECKBOX11, _("sym"), wxDefaultPosition, wxDefaultSize, wxCHK_3STATE|wxCHK_ALLOW_3RD_STATE_FOR_USER, wxDefaultValidator, _T("ID_CHECKBOX11"));
    m_checkIndivSym->SetValue(false);
    m_checkIndivSym->SetToolTip(_("Symbol control"));
    BoxSizer5->Add(m_checkIndivSym, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_checkIndivPer = new wxCheckBox(this, ID_CHECKBOX6, _("per"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    m_checkIndivPer->SetValue(false);
    m_checkIndivPer->SetToolTip(_("Individual period or all\?"));
    BoxSizer5->Add(m_checkIndivPer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_checkIndivStrat = new wxCheckBox(this, ID_CHECKBOX4, _("str"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    m_checkIndivStrat->SetValue(true);
    m_checkIndivStrat->SetToolTip(_("Single strategy"));
    BoxSizer5->Add(m_checkIndivStrat, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(BoxSizer5, 1, wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_butTF2Dialog = new wxButton(this, ID_BUTTON8, _("TF2"), wxDefaultPosition, wxSize(35,-1), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    m_butTF2Dialog->SetToolTip(_("Testing Framework"));
    BoxSizer6->Add(m_butTF2Dialog, 0, wxALL|wxEXPAND, 5);
    m_butOptiDialog = new wxButton(this, ID_BUTTON7, _("Opt"), wxDefaultPosition, wxSize(35,-1), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    m_butOptiDialog->SetToolTip(_("Optimization"));
    BoxSizer6->Add(m_butOptiDialog, 0, wxALL|wxEXPAND, 5);
    m_butMLDialog = new wxButton(this, ID_BUTTON9, _("ML"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    m_butMLDialog->SetMinSize(wxSize(35,-1));
    m_butMLDialog->SetToolTip(_("Machine Learning"));
    BoxSizer6->Add(m_butMLDialog, 0, wxALL|wxEXPAND, 5);
    m_butTS = new wxButton(this, ID_BUTTON10, _("TSA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    m_butTS->SetMinSize(wxSize(35,-1));
    m_butTS->SetToolTip(_("Time Series Analysis"));
    BoxSizer6->Add(m_butTS, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer6->Add(BoxSizer6, 1, wxEXPAND, 5);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    m_butSigIdClear = new wxButton(this, ID_BUTTON3, _("Clr"), wxDefaultPosition, wxSize(35,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer7->Add(m_butSigIdClear, 0, wxALL|wxEXPAND, 5);
    m_txtSigId = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer7->Add(m_txtSigId, 0, wxALL|wxEXPAND, 5);
    m_butSigIdApply = new wxButton(this, ID_BUTTON4, _("App"), wxDefaultPosition, wxSize(35,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    m_butSigIdApply->SetToolTip(_("Apply date string"));
    BoxSizer7->Add(m_butSigIdApply, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer6->Add(BoxSizer7, 1, wxEXPAND, 5);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    m_choicePlot = new MyChoiceEnum(this, ID_CHOICE8, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE8"));
    m_choicePlot->Append(_("asd"));
    BoxSizer10->Add(m_choicePlot, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_checkRepeat = new wxCheckBox(this, ID_CHECKBOX5, _("rp"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    m_checkRepeat->SetValue(false);
    m_checkRepeat->SetToolTip(_("Repeat or quit\?"));
    BoxSizer10->Add(m_checkRepeat, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_checkSimulMT = new wxCheckBox(this, ID_CHECKBOX8, _("mt"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    m_checkSimulMT->SetValue(false);
    m_checkSimulMT->SetToolTip(_("Multithreaded\?"));
    BoxSizer10->Add(m_checkSimulMT, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(BoxSizer10, 1, wxEXPAND, 5);
    BoxSizer1->Add(StaticBoxSizer6, 0, wxEXPAND, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_butLoad = new wxButton(this, ID_BUTTON2, _("Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_butLoad->Hide();
    BoxSizer4->Add(m_butLoad, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_butSave = new wxButton(this, ID_BUTTON1, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    m_butSave->Hide();
    BoxSizer4->Add(m_butSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 0, wxBOTTOM|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    m_status = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    m_status->SetFieldsCount(1,__wxStatusBarWidths_1);
    m_status->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(m_status);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_CHOICE7,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_CHOICE13,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::Onm_choiceDataSrcSelect);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::Onm_choiceYearStartSelect);
    Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::Onm_choiceYearStartSelect);
    Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    Connect(ID_CHOICE6,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxConfQTFrame::Onm_sliderBarsCmdScrollThumbRelease);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butClearBarClick);
    Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butPlotDialogClick);
    Connect(ID_CHOICE9,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHOICE10,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHOICE11,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHOICE12,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_QT);
    Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butTF2DialogClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butOptiDialogClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butMLDialogClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butTSClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butSigIdClearClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butSigIdApplyClick);
    Connect(ID_CHOICE8,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_TF);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::Onm_butLoadClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfQTFrame::On_General);
    //*)

    try
    {
        Init();
    }
    catch (std::exception & ex)
    {
        wxMessageBox(wxString::From8BitData(ex.what()), "Exception on Init!");
    }
}

wxConfQTFrame::~wxConfQTFrame()
{
    //m_confSym.Write();
    //(*Destroy(wxConfQTFrame)
    //*)
}

void wxConfQTFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxConfQTFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

