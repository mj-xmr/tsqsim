#ifndef DIALOGTS_H
#define DIALOGTS_H

#include <Maps/MapSpin.hpp>
#include <Maps/MapCheckbox.hpp>
#include <Maps/MapChoiceEnum.hpp>
#include <MyChoiceEnum.h>

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogTS)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxButton;
	class wxCheckBox;
	class wxChoice;
	class wxStaticBoxSizer;
	class wxTextCtrl;
	//*)
#endif
//(*Headers(DialogTS)
class wxSpinCtrl;
class wxSpinEvent;
//*)
#include <ConfigTS.h>

#include <STD/Vector.hpp>

class DialogTS : public wxDialog
{
	public:

		DialogTS(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DialogTS();

		//(*Declarations(DialogTS)
		MyChoiceEnum* m_choicePredType;
		MyChoiceEnum* m_choiceSeriesType;
		wxBoxSizer* m_sizerBools;
		wxButton* Button1;
		wxButton* m_butOK;
		wxButton* m_butScriptText;
		wxButton* m_butScriptTextGen;
		wxButton* m_butScriptTextOpen;
		wxButton* m_butScriptTextOpenGen;
		wxButton* m_butScriptTextOpenPy;
		wxButton* m_butScriptTextOpenR;
		wxButton* m_butScriptTextPy;
		wxButton* m_butScriptTextR;
		wxCheckBox* m_chkTechs;
		wxSpinCtrl* m_spinLagACF;
		wxSpinCtrl* m_spinPeriodSeasonal;
		wxTextCtrl* m_txtScriptPath;
		wxTextCtrl* m_txtScriptPathGen;
		wxTextCtrl* m_txtScriptPathPy;
		wxTextCtrl* m_txtScriptPathR;
		//*)

		ConfigTS m_confTS;

	protected:

		//(*Identifiers(DialogTS)
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_TEXTCTRL4;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_CHOICE1;
		static const long ID_CHOICE2;
		static const long ID_CHECKBOX12;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		//*)

	private:
	    void ReadSelections();
        void RestoreConf();
        void Init();

		//(*Handlers(DialogTS)
		void Onm_butScriptTextClick(wxCommandEvent& event);
		void OnTS(wxCommandEvent& event);
		void Onm_butScriptTextOpenClick(wxCommandEvent& event);
		void Onm_butScriptTextRClick(wxCommandEvent& event);
		void Onm_butScriptTextOpenRClick(wxCommandEvent& event);
		void Onm_butScriptTextOpenGenClick(wxCommandEvent& event);
		void Onm_butScriptTextGenClick(wxCommandEvent& event);
		void Onm_spinChange(wxSpinEvent& event);
		void Onm_butScriptTextPyClick(wxCommandEvent& event);
		void Onm_butScriptTextOpenPyClick(wxCommandEvent& event);
		//*)
        MapCheckbox     m_mapCheckbox;
        MapChoiceEnum   m_mapChoice;
		MapSpin         m_mapSpin;
		std::vector<IMapControl *> m_maps;


		DECLARE_EVENT_TABLE()
};

#endif
