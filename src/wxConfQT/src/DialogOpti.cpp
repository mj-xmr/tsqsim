#include "wx_pch.h"
#include "DialogOpti.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DialogOpti)
	#include <wx/checkbox.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/string.h>
	#include <wx/stattext.h>
	#include <wx/choice.h>
	//*)
#endif
//(*InternalHeaders(DialogOpti)
#include <wx/spinctrl.h>
//*)

//(*IdInit(DialogOpti)
const long DialogOpti::ID_CHOICE1 = wxNewId();
const long DialogOpti::ID_CHOICE2 = wxNewId();
const long DialogOpti::ID_CHOICE3 = wxNewId();
const long DialogOpti::ID_SPINCTRL3 = wxNewId();
const long DialogOpti::ID_SPINCTRL4 = wxNewId();
const long DialogOpti::ID_CHECKBOX2 = wxNewId();
const long DialogOpti::ID_CHECKBOX9 = wxNewId();
const long DialogOpti::ID_CHECKBOX3 = wxNewId();
const long DialogOpti::ID_CHECKBOX4 = wxNewId();
const long DialogOpti::ID_CHECKBOX5 = wxNewId();
const long DialogOpti::ID_CHECKBOX6 = wxNewId();
const long DialogOpti::ID_CHECKBOX8 = wxNewId();
const long DialogOpti::ID_CHECKBOX7 = wxNewId();
const long DialogOpti::ID_SPINCTRL1 = wxNewId();
const long DialogOpti::ID_STATICTEXT1 = wxNewId();
const long DialogOpti::ID_SPINCTRL2 = wxNewId();
const long DialogOpti::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DialogOpti,wxDialog)
	//(*EventTable(DialogOpti)
	//*)
END_EVENT_TABLE()

DialogOpti::DialogOpti(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DialogOpti)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, id, _T("Opti"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxPoint(375,-1));
	m_sizerTop = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	m_choiceOpti = new MyChoiceEnum(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer2->Add(m_choiceOpti, 0, wxALL|wxEXPAND, 5);
	m_choiceOptiMethod = new MyChoiceEnum(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	BoxSizer2->Add(m_choiceOptiMethod, 0, wxALL|wxEXPAND, 5);
	m_choiceOptiGoal = new MyChoiceEnum(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	BoxSizer2->Add(m_choiceOptiGoal, 0, wxALL|wxEXPAND, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Monte Carlo"));
	m_spinRandomSamples = new wxSpinCtrl(this, ID_SPINCTRL3, _T("100"), wxDefaultPosition, wxSize(130,-1), 0, 1, 1000, 100, _T("ID_SPINCTRL3"));
	m_spinRandomSamples->SetValue(_T("100"));
	m_spinRandomSamples->SetToolTip(_T("# random samples"));
	StaticBoxSizer1->Add(m_spinRandomSamples, 0, wxALL, 5);
	m_spinMaxESPromile = new wxSpinCtrl(this, ID_SPINCTRL4, _T("10"), wxDefaultPosition, wxSize(130,-1), 0, 1, 1000, 10, _T("ID_SPINCTRL4"));
	m_spinMaxESPromile->SetValue(_T("10"));
	m_spinMaxESPromile->SetToolTip(_T("Early stop: Percentile max change of goal"));
	StaticBoxSizer1->Add(m_spinMaxESPromile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND, 5);
	m_sizerBools = new wxBoxSizer(wxVERTICAL);
	m_checkXval = new wxCheckBox(this, ID_CHECKBOX2, _T("Xval"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_checkXval->SetValue(false);
	m_checkXval->Hide();
	m_sizerBools->Add(m_checkXval, 0, wxALL|wxEXPAND, 5);
	m_checkXValExtendable = new wxCheckBox(this, ID_CHECKBOX9, _T("Xval Ext"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	m_checkXValExtendable->SetValue(false);
	m_checkXValExtendable->Hide();
	m_checkXValExtendable->SetToolTip(_T("Extendable"));
	m_sizerBools->Add(m_checkXValExtendable, 0, wxALL|wxEXPAND, 5);
	m_checkLast = new wxCheckBox(this, ID_CHECKBOX3, _T("Last"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_checkLast->SetValue(false);
	m_checkLast->Hide();
	m_sizerBools->Add(m_checkLast, 0, wxALL|wxEXPAND, 5);
	m_checkDense = new wxCheckBox(this, ID_CHECKBOX4, _T("Dense"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_checkDense->SetValue(false);
	m_checkDense->Hide();
	m_sizerBools->Add(m_checkDense, 0, wxALL|wxEXPAND, 5);
	m_checkRelease = new wxCheckBox(this, ID_CHECKBOX5, _T("Release"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_checkRelease->SetValue(true);
	m_checkRelease->Hide();
	m_sizerBools->Add(m_checkRelease, 0, wxALL|wxEXPAND, 5);
	m_checkVerbose = new wxCheckBox(this, ID_CHECKBOX6, _T("Verbose"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_checkVerbose->SetValue(false);
	m_checkVerbose->Hide();
	m_sizerBools->Add(m_checkVerbose, 0, wxALL|wxEXPAND, 5);
	m_checkGlobal = new wxCheckBox(this, ID_CHECKBOX8, _T("Global"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	m_checkGlobal->SetValue(false);
	m_checkGlobal->Hide();
	m_sizerBools->Add(m_checkGlobal, 0, wxALL|wxEXPAND, 5);
	m_checkNelder = new wxCheckBox(this, ID_CHECKBOX7, _T("Nelder"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	m_checkNelder->SetValue(false);
	m_checkNelder->Hide();
	m_sizerBools->Add(m_checkNelder, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(m_sizerBools, 1, wxALL|wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	m_spinNumBarsOpti = new wxSpinCtrl(this, ID_SPINCTRL1, _T("2000"), wxDefaultPosition, wxSize(80,-1), 0, 10, 1000000000, 2000, _T("ID_SPINCTRL1"));
	m_spinNumBarsOpti->SetValue(_T("2000"));
	BoxSizer4->Add(m_spinNumBarsOpti, 0, wxALL|wxEXPAND, 5);
	m_labDaysOpti = new wxStaticText(this, ID_STATICTEXT1, _T("days"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	m_labDaysOpti->SetToolTip(_T("Days"));
	BoxSizer4->Add(m_labDaysOpti, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer4, 0, wxALL|wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	m_spinPercent4XValid = new wxSpinCtrl(this, ID_SPINCTRL2, _T("20"), wxDefaultPosition, wxSize(80,-1), 0, 1, 100, 20, _T("ID_SPINCTRL2"));
	m_spinPercent4XValid->SetValue(_T("20"));
	m_spinPercent4XValid->SetToolTip(_T("Days"));
	BoxSizer5->Add(m_spinPercent4XValid, 1, wxALL|wxEXPAND, 5);
	m_labDaysXVal = new wxStaticText(this, ID_STATICTEXT2, _T("days"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer5->Add(m_labDaysXVal, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer5, 0, wxALL|wxEXPAND, 5);
	m_sizerTop->Add(BoxSizer2, 0, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	Button2 = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_butOK = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer3->Add(m_butOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerTop->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(m_sizerTop);
	m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogOpti::OnSpin);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogOpti::OnSpin);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogOpti::OnSpin);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogOpti::OnSpin);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogOpti::OnOpti);
	//*)

	try {
        Init();
        RestoreConf();
	}
	catch (const std::exception & exc)
	{
	    wxMessageBox(exc.what(), "Exception in Opti");
	}
	
}

DialogOpti::~DialogOpti()
{
	//(*Destroy(DialogOpti)
	//*)
}
