#include "wx_pch.h"
#include "DialogTS.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DialogTS)
	#include <wx/checkbox.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/string.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	//*)
#endif
//(*InternalHeaders(DialogTS)
//*)

//(*IdInit(DialogTS)
const long DialogTS::ID_TEXTCTRL1 = wxNewId();
const long DialogTS::ID_BUTTON1 = wxNewId();
const long DialogTS::ID_BUTTON2 = wxNewId();
const long DialogTS::ID_TEXTCTRL2 = wxNewId();
const long DialogTS::ID_BUTTON3 = wxNewId();
const long DialogTS::ID_BUTTON4 = wxNewId();
const long DialogTS::ID_CHOICE1 = wxNewId();
const long DialogTS::ID_CHOICE2 = wxNewId();
const long DialogTS::ID_CHECKBOX12 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DialogTS,wxDialog)
	//(*EventTable(DialogTS)
	//*)
END_EVENT_TABLE()

DialogTS::DialogTS(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DialogTS)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;

	Create(parent, id, _T("Time Series Analysis"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	m_sizerBools = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Script data xform"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	m_txtScriptPath = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	m_txtScriptPath->SetToolTip(_T("Path to the text script"));
	BoxSizer4->Add(m_txtScriptPath, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer1->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_butScriptText = new wxButton(this, ID_BUTTON1, _T("Find"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(m_butScriptText, 0, wxALL|wxEXPAND, 5);
	m_butScriptTextOpen = new wxButton(this, ID_BUTTON2, _T("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(m_butScriptTextOpen, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_sizerBools->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Script R Custom"));
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	m_txtScriptPathR = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer5->Add(m_txtScriptPathR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(BoxSizer5, 1, wxALL|wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	m_butScriptTextR = new wxButton(this, ID_BUTTON3, _T("Find"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer6->Add(m_butScriptTextR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_butScriptTextOpenR = new wxButton(this, ID_BUTTON4, _T("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer6->Add(m_butScriptTextOpenR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
	m_sizerBools->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Predictor type"));
	m_choicePredType = new MyChoiceEnum(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	m_choicePredType->SetToolTip(_T("Prediction type"));
	StaticBoxSizer3->Add(m_choicePredType, 0, wxALL|wxEXPAND, 5);
	m_sizerBools->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Series type"));
	m_choiceSeriesType = new MyChoiceEnum(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	StaticBoxSizer2->Add(m_choiceSeriesType, 0, wxALL|wxEXPAND, 5);
	m_sizerBools->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
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

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogTS::Onm_butScriptTextClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogTS::Onm_butScriptTextOpenClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogTS::Onm_butScriptTextRClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DialogTS::Onm_butScriptTextOpenRClick);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTS::OnTS);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DialogTS::OnTS);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DialogTS::OnTS);
	//*)

	try {
        Init();
        RestoreConf();
	}
	catch (const std::exception & exc)
	{
	    wxMessageBox(exc.what(), "Exception in TS");
	}
}

DialogTS::~DialogTS()
{
	//(*Destroy(DialogTS)
	//*)
}
