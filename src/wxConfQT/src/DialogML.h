#ifndef DIALOGML_H
#define DIALOGML_H

#include <Maps/MapSpin.hpp>
#include <Maps/MapCheckbox.hpp>
#include <Maps/MapChoiceEnum.hpp>
#include <MyChoiceEnum.h>

#include <STD/Vector.hpp>
#include "ConfigML.h"

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogML)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxCheckBox;
	class wxChoice;
	class wxStaticText;
	//*)
#endif
//(*Headers(DialogML)
class wxSpinCtrl;
class wxSpinEvent;
//*)

class DialogML: public wxDialog
{
	public:

		DialogML(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DialogML();

		//(*Declarations(DialogML)
		MyChoiceEnum* m_choiceDistType;
		MyChoiceEnum* m_choiceRDEType;
		MyChoiceEnum* m_choiceRFEType;
		wxBoxSizer* m_sizerBools;
		wxBoxSizer* m_sizerTop;
		wxCheckBox* m_checkAddInverseBars;
		wxCheckBox* m_checkFindHori;
		wxCheckBox* m_checkRelease;
		wxCheckBox* m_checkRemErratic;
		wxCheckBox* m_checkReusePCA;
		wxSpinCtrl* m_lenTechs;
		wxSpinCtrl* m_spinKFolds;
		wxSpinCtrl* m_spinLenTechsMax;
		wxSpinCtrl* m_spinLenTechsMin;
		wxSpinCtrl* m_spinPCA;
		wxSpinCtrl* m_spinPCANum;
		wxSpinCtrl* m_spinVerbosity;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		//*)

		ConfigML m_confML;

	protected:

		//(*Identifiers(DialogML)
		static const long ID_CHOICE1;
		static const long ID_CHOICE3;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL7;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL4;
		static const long ID_SPINCTRL5;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL6;
		//*)

	private:
	    void ReadSelections();
        void RestoreConf();
        void Init();

		//(*Handlers(DialogML)
		void OnML(wxCommandEvent& event);
		void OnSpin(wxSpinEvent& event);
		//*)

		MapChoiceEnum m_mapChoice;
		MapCheckbox m_mapCheckbox;
		MapSpin     m_mapSpin;
		std::vector<IMapControl *> m_maps;

		DECLARE_EVENT_TABLE()
};

#endif
