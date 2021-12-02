#ifndef DIALOGOPTI_H
#define DIALOGOPTI_H

#include "ConfigOpti.h"
#include <Maps/MapCheckbox.hpp>
#include <Maps/MapSpin.hpp>
#include <Maps/MapChoiceEnum.hpp>
#include "MyChoiceEnum.h"
#include <STD/Vector.hpp>

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogOpti)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxButton;
	class wxCheckBox;
	class wxChoice;
	class wxStaticBoxSizer;
	class wxStaticText;
	//*)
#endif
//(*Headers(DialogOpti)
class wxSpinCtrl;
class wxSpinEvent;
//*)

class DialogOpti: public wxDialog
{
	public:

		DialogOpti(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DialogOpti();

		//(*Declarations(DialogOpti)
		MyChoiceEnum* m_choiceOpti;
		MyChoiceEnum* m_choiceOptiGoal;
		MyChoiceEnum* m_choiceOptiMethod;
		wxBoxSizer* m_sizerBools;
		wxBoxSizer* m_sizerTop;
		wxButton* Button2;
		wxButton* m_butOK;
		wxCheckBox* m_checkDense;
		wxCheckBox* m_checkGlobal;
		wxCheckBox* m_checkLast;
		wxCheckBox* m_checkNelder;
		wxCheckBox* m_checkRelease;
		wxCheckBox* m_checkVerbose;
		wxCheckBox* m_checkXValExtendable;
		wxCheckBox* m_checkXval;
		wxSpinCtrl* m_spinMaxESPromile;
		wxSpinCtrl* m_spinNumBarsOpti;
		wxSpinCtrl* m_spinPercent4XValid;
		wxSpinCtrl* m_spinRandomSamples;
		wxStaticText* m_labDaysOpti;
		wxStaticText* m_labDaysXVal;
		//*)

		ConfigOpti m_confOpti;

	protected:

		//(*Identifiers(DialogOpti)
		static const long ID_CHOICE1;
		static const long ID_CHOICE2;
		static const long ID_CHOICE3;
		static const long ID_SPINCTRL3;
		static const long ID_SPINCTRL4;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX7;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT2;
		//*)

	private:
	    void ReadSelections();
        void RestoreConf();
        void Init();
        void React();
        void ReactWrite();
        void UpdateDayLabels();

		//(*Handlers(DialogOpti)
		void OnOpti(wxCommandEvent& event);
		void OnSpin(wxSpinEvent& event);
		//*)

		MapCheckbox m_mapCheckbox;
		MapChoiceEnum m_mapChoice;
		MapSpin     m_mapSpin;
		std::vector<IMapControl *> m_maps;

		DECLARE_EVENT_TABLE()
};

#endif
