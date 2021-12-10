#ifndef DIALOGPLOTS_H
#define DIALOGPLOTS_H

#include <Maps/MapCheckbox.hpp>

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogPlots)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxButton;
	class wxCheckBox;
	//*)
#endif
//(*Headers(DialogPlots)
//*)
#include <ConfigQTPlot.h>

class DialogPlots: public wxDialog
{
	public:

		DialogPlots(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DialogPlots();

		//(*Declarations(DialogPlots)
		wxBoxSizer* m_sizerBools;
		wxButton* Button1;
		wxButton* m_butOK;
		wxCheckBox* m_checkBet;
		wxCheckBox* m_chkCandles;
		wxCheckBox* m_chkDark;
		wxCheckBox* m_chkMA;
		wxCheckBox* m_chkProfit;
		wxCheckBox* m_chkSL;
		wxCheckBox* m_chkSR;
		wxCheckBox* m_chkSRgroups;
		wxCheckBox* m_chkSigSpec;
		wxCheckBox* m_chkSigTrade;
		wxCheckBox* m_chkSimul;
		wxCheckBox* m_chkStdDev;
		wxCheckBox* m_chkTPs;
		wxCheckBox* m_chkTechs;
		wxCheckBox* m_chkWknd;
		wxCheckBox* m_chkZZidx;
		wxCheckBox* m_chkZigZag;
		//*)

		ConfigQTPlot m_confQTPlot;

	protected:

		//(*Identifiers(DialogPlots)
		static const long ID_CHECKBOX17;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX16;
		static const long ID_CHECKBOX12;
		//*)

	private:
	    void ReadSelections();
        void RestoreConf();
        void Init();

		//(*Handlers(DialogPlots)
		void OnQTPlot(wxCommandEvent& event);
		//*)
        MapCheckbox m_mapCheckbox;


		DECLARE_EVENT_TABLE()
};

#endif
