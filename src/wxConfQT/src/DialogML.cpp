#include "wx_pch.h"
#include "DialogML.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DialogML)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(DialogML)
//*)

#include <wx/spinctrl.h>

//(*IdInit(DialogML)
const long DialogML::ID_CHOICE1 = wxNewId();
const long DialogML::ID_CHOICE3 = wxNewId();
const long DialogML::ID_CHOICE2 = wxNewId();
const long DialogML::ID_STATICTEXT1 = wxNewId();
const long DialogML::ID_SPINCTRL1 = wxNewId();
const long DialogML::ID_SPINCTRL7 = wxNewId();
const long DialogML::ID_STATICTEXT2 = wxNewId();
const long DialogML::ID_SPINCTRL2 = wxNewId();
const long DialogML::ID_SPINCTRL4 = wxNewId();
const long DialogML::ID_SPINCTRL5 = wxNewId();
const long DialogML::ID_STATICTEXT3 = wxNewId();
const long DialogML::ID_SPINCTRL3 = wxNewId();
const long DialogML::ID_CHECKBOX3 = wxNewId();
const long DialogML::ID_CHECKBOX1 = wxNewId();
const long DialogML::ID_CHECKBOX2 = wxNewId();
const long DialogML::ID_CHECKBOX4 = wxNewId();
const long DialogML::ID_CHECKBOX5 = wxNewId();
const long DialogML::ID_STATICTEXT4 = wxNewId();
const long DialogML::ID_SPINCTRL6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DialogML,wxDialog)
	//(*EventTable(DialogML)
	//*)
END_EVENT_TABLE()

DialogML::DialogML(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DialogML)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer7;

	Create(parent, id, _("ML"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	Move(wxPoint(375,-1));
	m_sizerTop = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	m_choiceRFEType = new MyChoiceEnum(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	m_choiceRFEType->SetToolTip(_("Recursive Feature Elimination type"));
	BoxSizer2->Add(m_choiceRFEType, 0, wxALL|wxEXPAND, 5);
	m_choiceRDEType = new MyChoiceEnum(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	m_choiceRDEType->SetToolTip(_("Recursive Data Elimination type"));
	BoxSizer2->Add(m_choiceRDEType, 0, wxALL|wxEXPAND, 5);
	m_choiceDistType = new MyChoiceEnum(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	m_choiceDistType->SetToolTip(_("Dist type"));
	BoxSizer2->Add(m_choiceDistType, 0, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("PCA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxEXPAND, 5);
	m_spinPCA = new wxSpinCtrl(this, ID_SPINCTRL1, _T("90"), wxDefaultPosition, wxSize(80,-1), 0, 0, 100, 90, _T("ID_SPINCTRL1"));
	m_spinPCA->SetValue(_T("90"));
	m_spinPCA->SetToolTip(_("PCA quality"));
	BoxSizer3->Add(m_spinPCA, 0, wxALL|wxEXPAND, 5);
	m_spinPCANum = new wxSpinCtrl(this, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxSize(80,-1), 0, 0, 100, 0, _T("ID_SPINCTRL7"));
	m_spinPCANum->SetValue(_T("0"));
	m_spinPCANum->SetToolTip(_("Num components"));
	BoxSizer3->Add(m_spinPCANum, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Hor"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer4->Add(StaticText2, 0, wxALL|wxEXPAND, 5);
	m_lenTechs = new wxSpinCtrl(this, ID_SPINCTRL2, _T("15"), wxDefaultPosition, wxSize(60,-1), 0, 1, 100, 15, _T("ID_SPINCTRL2"));
	m_lenTechs->SetValue(_T("15"));
	m_lenTechs->SetToolTip(_("Len techs"));
	BoxSizer4->Add(m_lenTechs, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer4, 0, wxEXPAND, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	m_spinLenTechsMin = new wxSpinCtrl(this, ID_SPINCTRL4, _T("1"), wxDefaultPosition, wxSize(60,-1), 0, 1, 100, 1, _T("ID_SPINCTRL4"));
	m_spinLenTechsMin->SetValue(_T("1"));
	BoxSizer7->Add(m_spinLenTechsMin, 0, wxALL|wxEXPAND, 5);
	m_spinLenTechsMax = new wxSpinCtrl(this, ID_SPINCTRL5, _T("1"), wxDefaultPosition, wxSize(60,-1), 0, 1, 100, 1, _T("ID_SPINCTRL5"));
	m_spinLenTechsMax->SetValue(_T("1"));
	BoxSizer7->Add(m_spinLenTechsMax, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer7, 0, wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Verb"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer5->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_spinVerbosity = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(80,-1), 0, 0, 2, 0, _T("ID_SPINCTRL3"));
	m_spinVerbosity->SetValue(_T("0"));
	BoxSizer5->Add(m_spinVerbosity, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer5, 0, wxEXPAND, 5);
	m_sizerBools = new wxBoxSizer(wxVERTICAL);
	m_checkRelease = new wxCheckBox(this, ID_CHECKBOX3, _("Release"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	m_checkRelease->SetValue(false);
	m_checkRelease->Hide();
	m_sizerBools->Add(m_checkRelease, 0, wxEXPAND, 5);
	m_checkAddInverseBars = new wxCheckBox(this, ID_CHECKBOX1, _("Inv bars"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_checkAddInverseBars->SetValue(false);
	m_checkAddInverseBars->Hide();
	m_sizerBools->Add(m_checkAddInverseBars, 0, wxEXPAND, 5);
	m_checkFindHori = new wxCheckBox(this, ID_CHECKBOX2, _("Find hori"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_checkFindHori->SetValue(false);
	m_checkFindHori->Hide();
	m_sizerBools->Add(m_checkFindHori, 0, wxEXPAND, 5);
	m_checkRemErratic = new wxCheckBox(this, ID_CHECKBOX4, _("Rem erratic"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_checkRemErratic->SetValue(false);
	m_checkRemErratic->Hide();
	m_sizerBools->Add(m_checkRemErratic, 0, wxEXPAND, 5);
	m_checkReusePCA = new wxCheckBox(this, ID_CHECKBOX5, _("Reuse PCA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	m_checkReusePCA->SetValue(false);
	m_checkReusePCA->Hide();
	m_sizerBools->Add(m_checkReusePCA, 0, wxEXPAND, 5);
	BoxSizer2->Add(m_sizerBools, 0, wxALL|wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("kFolds"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer6->Add(StaticText4, 0, wxALL|wxEXPAND, 5);
	m_spinKFolds = new wxSpinCtrl(this, ID_SPINCTRL6, _T("3"), wxDefaultPosition, wxDefaultSize, 0, 1, 50, 3, _T("ID_SPINCTRL6"));
	m_spinKFolds->SetValue(_T("3"));
	BoxSizer6->Add(m_spinKFolds, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
	m_sizerTop->Add(BoxSizer2, 0, wxEXPAND, 5);
	SetSizer(m_sizerTop);
	m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_SPINCTRL7,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogML::OnML);
	Connect(ID_SPINCTRL6,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DialogML::OnSpin);
	//*)

	try {
        Init();
	}
	catch (const std::exception & exc)
	{
	    wxMessageBox(exc.what(), "Exception in ML");
	}
}

DialogML::~DialogML()
{
	//(*Destroy(DialogML)
	//*)
}
