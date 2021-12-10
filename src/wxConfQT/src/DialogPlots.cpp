#include "wx_pch.h"
#include "DialogPlots.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DialogPlots)
	#include <wx/checkbox.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(DialogPlots)
//*)

//(*IdInit(DialogPlots)
const long DialogPlots::ID_CHECKBOX17 = wxNewId();
const long DialogPlots::ID_CHECKBOX13 = wxNewId();
const long DialogPlots::ID_CHECKBOX11 = wxNewId();
const long DialogPlots::ID_CHECKBOX1 = wxNewId();
const long DialogPlots::ID_CHECKBOX3 = wxNewId();
const long DialogPlots::ID_CHECKBOX9 = wxNewId();
const long DialogPlots::ID_CHECKBOX2 = wxNewId();
const long DialogPlots::ID_CHECKBOX4 = wxNewId();
const long DialogPlots::ID_CHECKBOX5 = wxNewId();
const long DialogPlots::ID_CHECKBOX6 = wxNewId();
const long DialogPlots::ID_CHECKBOX7 = wxNewId();
const long DialogPlots::ID_CHECKBOX8 = wxNewId();
const long DialogPlots::ID_CHECKBOX10 = wxNewId();
const long DialogPlots::ID_CHECKBOX15 = wxNewId();
const long DialogPlots::ID_CHECKBOX14 = wxNewId();
const long DialogPlots::ID_CHECKBOX16 = wxNewId();
const long DialogPlots::ID_CHECKBOX12 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DialogPlots,wxDialog)
	//(*EventTable(DialogPlots)
	//*)
END_EVENT_TABLE()

DialogPlots::DialogPlots(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DialogPlots)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, _T("Plots"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	Move(wxPoint(375,-1));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	m_sizerBools = new wxBoxSizer(wxVERTICAL);
	m_chkDark = new wxCheckBox(this, ID_CHECKBOX17, _T("Dark"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	m_chkDark->SetValue(false);
	m_chkDark->Hide();
	m_sizerBools->Add(m_chkDark, 0, wxEXPAND, 5);
	m_chkCandles = new wxCheckBox(this, ID_CHECKBOX13, _T("Candles"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	m_chkCandles->SetValue(true);
	m_chkCandles->Hide();
	m_sizerBools->Add(m_chkCandles, 1, wxEXPAND, 5);
	m_chkSigSpec = new wxCheckBox(this, ID_CHECKBOX11, _T("Sig Spec"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	m_chkSigSpec->SetValue(true);
	m_chkSigSpec->Hide();
	m_sizerBools->Add(m_chkSigSpec, 0, wxEXPAND, 5);
	m_chkSigTrade = new wxCheckBox(this, ID_CHECKBOX1, _T("Sig Trade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_chkSigTrade->SetValue(true);
	m_chkSigTrade->Hide();
	m_sizerBools->Add(m_chkSigTrade, 0, wxEXPAND, 5);
	m_chkSimul = new wxCheckBox(this, ID_CHECKBOX3, _T("Simul"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_chkSimul->SetValue(true);
	m_chkSimul->Hide();
	m_sizerBools->Add(m_chkSimul, 0, wxEXPAND, 5);
	m_chkSL = new wxCheckBox(this, ID_CHECKBOX9, _T("SL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	m_chkSL->SetValue(true);
	m_chkSL->Hide();
	m_sizerBools->Add(m_chkSL, 0, wxEXPAND, 5);
	m_chkProfit = new wxCheckBox(this, ID_CHECKBOX2, _T("Profit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_chkProfit->SetValue(true);
	m_chkProfit->Hide();
	m_sizerBools->Add(m_chkProfit, 0, wxEXPAND, 5);
	m_chkTPs = new wxCheckBox(this, ID_CHECKBOX4, _T("TPs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_chkTPs->SetValue(true);
	m_chkTPs->Hide();
	m_sizerBools->Add(m_chkTPs, 0, wxEXPAND, 5);
	m_chkSR = new wxCheckBox(this, ID_CHECKBOX5, _T("SR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_chkSR->SetValue(true);
	m_chkSR->Hide();
	m_sizerBools->Add(m_chkSR, 0, wxEXPAND, 5);
	m_chkSRgroups = new wxCheckBox(this, ID_CHECKBOX6, _T("SR grp"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_chkSRgroups->SetValue(true);
	m_chkSRgroups->Hide();
	m_sizerBools->Add(m_chkSRgroups, 0, wxEXPAND, 5);
	m_chkMA = new wxCheckBox(this, ID_CHECKBOX7, _T("MA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	m_chkMA->SetValue(true);
	m_chkMA->Hide();
	m_sizerBools->Add(m_chkMA, 0, wxEXPAND, 5);
	m_chkStdDev = new wxCheckBox(this, ID_CHECKBOX8, _T("Std Dev"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	m_chkStdDev->SetValue(false);
	m_chkStdDev->Hide();
	m_sizerBools->Add(m_chkStdDev, 0, wxEXPAND, 5);
	m_chkZigZag = new wxCheckBox(this, ID_CHECKBOX10, _T("ZigZag"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	m_chkZigZag->SetValue(true);
	m_chkZigZag->Hide();
	m_sizerBools->Add(m_chkZigZag, 0, wxEXPAND, 5);
	m_chkZZidx = new wxCheckBox(this, ID_CHECKBOX15, _T("ZZindx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	m_chkZZidx->SetValue(false);
	m_chkZZidx->Hide();
	m_sizerBools->Add(m_chkZZidx, 0, wxEXPAND, 5);
	m_chkWknd = new wxCheckBox(this, ID_CHECKBOX14, _T("Weekend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	m_chkWknd->SetValue(true);
	m_chkWknd->Hide();
	m_sizerBools->Add(m_chkWknd, 0, wxEXPAND, 5);
	m_checkBet = new wxCheckBox(this, ID_CHECKBOX16, _T("Bet"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	m_checkBet->SetValue(false);
	m_checkBet->Hide();
	m_sizerBools->Add(m_checkBet, 0, wxEXPAND, 5);
	m_chkTechs = new wxCheckBox(this, ID_CHECKBOX12, _T("Techs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	m_chkTechs->SetValue(true);
	m_chkTechs->Hide();
	m_sizerBools->Add(m_chkTechs, 0, wxEXPAND, 5);
	BoxSizer1->Add(m_sizerBools, 0, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	Button1 = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_butOK = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer3->Add(m_butOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogPlots::OnQTPlot);
	//*)

	try {
        Init();
        RestoreConf();
	}
	catch (const std::exception & exc)
	{
	    wxMessageBox(exc.what(), "Exception in Plots");
	}
}

DialogPlots::~DialogPlots()
{
	//(*Destroy(DialogPlots)
	//*)
}

