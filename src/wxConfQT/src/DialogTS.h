#ifndef DIALOGTS_H
#define DIALOGTS_H

#include <Maps/MapCheckbox.hpp>

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogTS)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxButton;
	class wxCheckBox;
	class wxStaticBoxSizer;
	class wxTextCtrl;
	//*)
#endif
//(*Headers(DialogTS)
//*)
#include <ConfigTS.h>

class DialogTS : public wxDialog
{
	public:

		DialogTS(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DialogTS();

		//(*Declarations(DialogTS)
		wxBoxSizer* m_sizerBools;
		wxButton* Button1;
		wxButton* m_butOK;
		wxButton* m_butScriptText;
		wxButton* m_butScriptTextOpen;
		wxCheckBox* m_chkTechs;
		wxTextCtrl* m_txtScriptPath;
		//*)

		ConfigTS m_confTS;

	protected:

		//(*Identifiers(DialogTS)
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_CHECKBOX12;
		//*)

	private:
	    void ReadSelections();
        void RestoreConf();
        void Init();

		//(*Handlers(DialogTS)
		void Onm_butScriptTextClick(wxCommandEvent& event);
		void OnTS(wxCommandEvent& event);
		void Onm_butScriptTextOpenClick(wxCommandEvent& event);
		//*)
        MapCheckbox m_mapCheckbox;


		DECLARE_EVENT_TABLE()
};

#endif
