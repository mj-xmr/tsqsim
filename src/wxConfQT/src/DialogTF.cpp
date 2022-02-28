#include "wx_pch.h"
#include "DialogTF.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DialogTF)
	#include <wx/checkbox.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/string.h>
	#include <wx/stattext.h>
	#include <wx/choice.h>
	//*)
#endif
//(*InternalHeaders(DialogTF)
#include <wx/spinctrl.h>
//*)

//(*IdInit(DialogTF)
const long DialogTF::ID_CHOICE5 = wxNewId();
const long DialogTF::ID_CHOICE1 = wxNewId();
const long DialogTF::ID_CHOICE2 = wxNewId();
const long DialogTF::ID_CHOICE3 = wxNewId();
const long DialogTF::ID_CHOICE4 = wxNewId();
const long DialogTF::ID_CHECKBOX17 = wxNewId();
const long DialogTF::ID_CHECKBOX1 = wxNewId();
const long DialogTF::ID_CHECKBOX15 = wxNewId();
const long DialogTF::ID_CHECKBOX10 = wxNewId();
const long DialogTF::ID_CHECKBOX11 = wxNewId();
const long DialogTF::ID_CHECKBOX12 = wxNewId();
const long DialogTF::ID_CHECKBOX13 = wxNewId();
const long DialogTF::ID_CHECKBOX14 = wxNewId();
const long DialogTF::ID_CHECKBOX7 = wxNewId();
const long DialogTF::ID_CHECKBOX6 = wxNewId();
const long DialogTF::ID_CHECKBOX8 = wxNewId();
const long DialogTF::ID_CHECKBOX3 = wxNewId();
const long DialogTF::ID_CHECKBOX2 = wxNewId();
const long DialogTF::ID_CHECKBOX4 = wxNewId();
const long DialogTF::ID_CHECKBOX16 = wxNewId();
const long DialogTF::ID_CHECKBOX5 = wxNewId();
const long DialogTF::ID_CHECKBOX18 = wxNewId();
const long DialogTF::ID_CHECKBOX20 = wxNewId();
const long DialogTF::ID_CHECKBOX21 = wxNewId();
const long DialogTF::ID_STATICTEXT1 = wxNewId();
const long DialogTF::ID_SPINCTRL3 = wxNewId();
const long DialogTF::ID_SPINCTRL4 = wxNewId();
const long DialogTF::ID_CHECKBOX19 = wxNewId();
const long DialogTF::ID_STATICTEXT2 = wxNewId();
const long DialogTF::ID_SPINCTRL1 = wxNewId();
const long DialogTF::ID_STATICTEXT3 = wxNewId();
const long DialogTF::ID_SPINCTRL2 = wxNewId();
const long DialogTF::ID_STATICTEXT4 = wxNewId();
const long DialogTF::ID_SPINCTRL5 = wxNewId();
const long DialogTF::ID_SPINCTRL6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DialogTF,wxDialog)
	//(*EventTable(DialogTF)
	//*)
END_EVENT_TABLE()

DialogTF::DialogTF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DialogTF)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* m_sizerMain;

	Create(parent, wxID_ANY, _T("TF2"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	Move(wxPoint(250,-1));
	m_sizerTop = new wxBoxSizer(wxVERTICAL);
	m_sizerMain = new wxBoxSizer(wxVERTICAL);
	m_choiceSim = new MyChoiceEnum(this, ID_CHOICE5, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
	m_choiceSim->SetToolTip(_T("Simulator type"));
	m_sizerMain->Add(m_choiceSim, 0, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	m_choiceYearStartTF = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	m_choiceYearStartTF->SetSelection( m_choiceYearStartTF->Append(_T("2000")) );
	BoxSizer4->Add(m_choiceYearStartTF, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_choiceYearEndTF = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	m_choiceYearEndTF->SetSelection( m_choiceYearEndTF->Append(_T("2000")) );
	BoxSizer4->Add(m_choiceYearEndTF, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerMain->Add(BoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	m_choiceMonthStartTF = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	m_choiceMonthStartTF->SetSelection( m_choiceMonthStartTF->Append(_T("12")) );
	BoxSizer5->Add(m_choiceMonthStartTF, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_choiceMonthEndTF = new wxChoice(this, ID_CHOICE4, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
	m_choiceMonthEndTF->SetSelection( m_choiceMonthEndTF->Append(_T("12")) );
	BoxSizer5->Add(m_choiceMonthEndTF, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerMain->Add(BoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerBools = new wxBoxSizer(wxVERTICAL);
	m_checkPotentialProfit = new wxCheckBox(this, ID_CHECKBOX17, _T("Potential"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	m_checkPotentialProfit->SetValue(false);
	m_checkPotentialProfit->Hide();
	m_sizerBools->Add(m_checkPotentialProfit, 0, wxEXPAND, 5);
	m_checkNetworked = new wxCheckBox(this, ID_CHECKBOX1, _T("Networked"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_checkNetworked->SetValue(false);
	m_checkNetworked->Hide();
	m_sizerBools->Add(m_checkNetworked, 0, wxEXPAND, 5);
	m_checkNetworkedCV = new wxCheckBox(this, ID_CHECKBOX15, _T("Networked CV"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	m_checkNetworkedCV->SetValue(false);
	m_checkNetworkedCV->Hide();
	m_sizerBools->Add(m_checkNetworkedCV, 0, wxEXPAND, 5);
	m_optimCostly = new wxCheckBox(this, ID_CHECKBOX10, _T("OptiCostly"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	m_optimCostly->SetValue(false);
	m_optimCostly->Hide();
	m_sizerBools->Add(m_optimCostly, 0, wxEXPAND, 5);
	m_checkCorrelCalc = new wxCheckBox(this, ID_CHECKBOX11, _T("Correl calc"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	m_checkCorrelCalc->SetValue(false);
	m_checkCorrelCalc->Hide();
	m_sizerBools->Add(m_checkCorrelCalc, 0, wxEXPAND, 5);
	m_checkCorrelUse = new wxCheckBox(this, ID_CHECKBOX12, _T("Correl use"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	m_checkCorrelUse->SetValue(false);
	m_checkCorrelUse->Hide();
	m_sizerBools->Add(m_checkCorrelUse, 0, wxEXPAND, 5);
	m_checkCorrelAdapt = new wxCheckBox(this, ID_CHECKBOX13, _T("Correl adapt"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	m_checkCorrelAdapt->SetValue(false);
	m_checkCorrelAdapt->Hide();
	m_sizerBools->Add(m_checkCorrelAdapt, 0, wxEXPAND, 5);
	m_checkExperimental = new wxCheckBox(this, ID_CHECKBOX14, _T("Experim"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	m_checkExperimental->SetValue(false);
	m_checkExperimental->Hide();
	m_sizerBools->Add(m_checkExperimental, 0, wxEXPAND, 5);
	m_checkPyServer = new wxCheckBox(this, ID_CHECKBOX7, _T("PyServ"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	m_checkPyServer->SetValue(false);
	m_checkPyServer->Hide();
	m_sizerBools->Add(m_checkPyServer, 0, wxEXPAND, 5);
	m_checkFullData = new wxCheckBox(this, ID_CHECKBOX6, _T("FullDat"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_checkFullData->SetValue(false);
	m_checkFullData->Hide();
	m_sizerBools->Add(m_checkFullData, 0, wxEXPAND, 5);
	m_checkBlacklist = new wxCheckBox(this, ID_CHECKBOX8, _T("Blacklist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	m_checkBlacklist->SetValue(false);
	m_checkBlacklist->Hide();
	m_sizerBools->Add(m_checkBlacklist, 0, wxEXPAND, 5);
	m_checkUseTicks = new wxCheckBox(this, ID_CHECKBOX3, _T("Ticks"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_checkUseTicks->SetValue(false);
	m_checkUseTicks->Hide();
	m_sizerBools->Add(m_checkUseTicks, 0, wxEXPAND, 5);
	m_checkTechUpdate = new wxCheckBox(this, ID_CHECKBOX2, _T("TechUp"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_checkTechUpdate->SetValue(false);
	m_checkTechUpdate->Hide();
	m_sizerBools->Add(m_checkTechUpdate, 0, wxEXPAND, 5);
	m_checkTrain = new wxCheckBox(this, ID_CHECKBOX4, _T("Train"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_checkTrain->SetValue(false);
	m_checkTrain->Hide();
	m_sizerBools->Add(m_checkTrain, 0, wxEXPAND, 5);
	m_checkPlotCompound = new wxCheckBox(this, ID_CHECKBOX16, _T("Plot Compound"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	m_checkPlotCompound->SetValue(false);
	m_checkPlotCompound->Hide();
	m_sizerBools->Add(m_checkPlotCompound, 0, wxEXPAND, 5);
	m_checkPlots = new wxCheckBox(this, ID_CHECKBOX5, _T("PyPlt"), wxDefaultPosition, wxDefaultSize, wxCHK_3STATE|wxCHK_ALLOW_3RD_STATE_FOR_USER, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_checkPlots->SetValue(false);
	m_checkPlots->Hide();
	m_sizerBools->Add(m_checkPlots, 0, wxEXPAND, 5);
	m_checkRandomBars = new wxCheckBox(this, ID_CHECKBOX18, _T("Random bars"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
	m_checkRandomBars->SetValue(false);
	m_checkRandomBars->Hide();
	m_sizerBools->Add(m_checkRandomBars, 0, wxEXPAND, 5);
	m_checkSingleThreadedAll = new wxCheckBox(this, ID_CHECKBOX20, _T("Single threaded"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
	m_checkSingleThreadedAll->SetValue(false);
	m_checkSingleThreadedAll->Hide();
	m_sizerBools->Add(m_checkSingleThreadedAll, 0, wxEXPAND, 5);
	m_checkStatsSummary = new wxCheckBox(this, ID_CHECKBOX21, _T("Stats summary"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX21"));
	m_checkStatsSummary->SetValue(false);
	m_checkStatsSummary->Hide();
	m_sizerBools->Add(m_checkStatsSummary, 0, wxEXPAND, 5);
	m_sizerMain->Add(m_sizerBools, 0, wxALL|wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("%/S"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer6->Add(StaticText1, 0, wxALL|wxEXPAND, 5);
	m_spinRandomPercent = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(40,-1), 0, 0, 100, 0, _T("ID_SPINCTRL3"));
	m_spinRandomPercent->SetValue(_T("0"));
	m_spinRandomPercent->SetToolTip(_T("Variance in %"));
	BoxSizer6->Add(m_spinRandomPercent, 0, wxALL|wxEXPAND, 5);
	m_spinRandomSeed = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxSize(40,-1), 0, 0, 100, 0, _T("ID_SPINCTRL4"));
	m_spinRandomSeed->SetValue(_T("0"));
	m_spinRandomSeed->SetToolTip(_T("Seed"));
	BoxSizer6->Add(m_spinRandomSeed, 0, wxALL|wxEXPAND, 5);
	m_sizerMain->Add(BoxSizer6, 0, wxEXPAND, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	m_checkFilter = new wxCheckBox(this, ID_CHECKBOX19, _T("Filter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
	m_checkFilter->SetValue(false);
	m_checkFilter->Hide();
	BoxSizer7->Add(m_checkFilter, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer7->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_spinSLMulFilter = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(60,-1), 0, 0, 40, 0, _T("ID_SPINCTRL1"));
	m_spinSLMulFilter->SetValue(_T("0"));
	m_spinSLMulFilter->SetToolTip(_T("Mul spread"));
	BoxSizer7->Add(m_spinSLMulFilter, 0, wxEXPAND, 5);
	m_sizerMain->Add(BoxSizer7, 1, wxEXPAND, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Cores"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer1->Add(StaticText3, 0, wxALL, 5);
	m_spinThreads = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxSize(30,-1), 0, 0, 8, 0, _T("ID_SPINCTRL2"));
	m_spinThreads->SetValue(_T("0"));
	m_spinThreads->SetToolTip(_T("Threads num"));
	BoxSizer1->Add(m_spinThreads, 1, wxALL|wxEXPAND, 5);
	m_sizerMain->Add(BoxSizer1, 1, wxEXPAND, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("Exper"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer8->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_spinExperim1 = new wxSpinCtrl(this, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100000, 0, _T("ID_SPINCTRL5"));
	m_spinExperim1->SetValue(_T("0"));
	m_spinExperim1->SetMinSize(wxSize(50,30));
	m_spinExperim1->SetToolTip(_T("Experim 1"));
	BoxSizer8->Add(m_spinExperim1, 0, wxALL|wxEXPAND, 5);
	m_spinExperim2 = new wxSpinCtrl(this, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100000, 0, _T("ID_SPINCTRL6"));
	m_spinExperim2->SetValue(_T("0"));
	m_spinExperim2->SetMinSize(wxSize(50,0));
	m_spinExperim2->SetToolTip(_T("Experim 2"));
	BoxSizer8->Add(m_spinExperim2, 0, wxALL|wxEXPAND, 5);
	m_sizerMain->Add(BoxSizer8, 0, wxEXPAND, 5);
	m_sizerTop->Add(m_sizerMain, 1, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	Button1 = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerTop->Add(BoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(m_sizerTop);
	m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);

	Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX20,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_CHECKBOX21,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(ID_CHECKBOX19,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(ID_SPINCTRL6,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogTF::Onm_spinSLMulFilterChange);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogTF::OnTF);
	//*)

	try {
        Init();
	}
	catch (const std::exception & exc)
	{
	    wxMessageBox(exc.what(), "Exception in TF");
	}
}

DialogTF::~DialogTF()
{
	//(*Destroy(DialogTF)
	//*)
}
