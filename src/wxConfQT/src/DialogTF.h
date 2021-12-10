#ifndef DIALOGTF_H
#define DIALOGTF_H

#include <ConfigTF2.h>
#include <Maps/MapCheckbox.hpp>
#include <Maps/MapSpin.hpp>
#include <Maps/MapChoiceEnum.hpp>
#include "MyChoiceEnum.h"
#include <STD/Vector.hpp>

#ifndef WX_PRECOMP
	//(*HeadersPCH(DialogTF)
	#include <wx/dialog.h>
	class wxBoxSizer;
	class wxButton;
	class wxCheckBox;
	class wxChoice;
	class wxStaticText;
	//*)
#endif
//(*Headers(DialogTF)
class wxSpinCtrl;
class wxSpinEvent;
//*)

class DialogTF: public wxDialog
{
	public:

		DialogTF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DialogTF();

		//(*Declarations(DialogTF)
		MyChoiceEnum* m_choiceSim;
		wxBoxSizer* m_sizerBools;
		wxBoxSizer* m_sizerTop;
		wxButton* Button1;
		wxButton* Button2;
		wxCheckBox* m_checkBlacklist;
		wxCheckBox* m_checkCorrelAdapt;
		wxCheckBox* m_checkCorrelCalc;
		wxCheckBox* m_checkCorrelUse;
		wxCheckBox* m_checkExperimental;
		wxCheckBox* m_checkFilter;
		wxCheckBox* m_checkFullData;
		wxCheckBox* m_checkNetworked;
		wxCheckBox* m_checkNetworkedCV;
		wxCheckBox* m_checkPlotCompound;
		wxCheckBox* m_checkPlots;
		wxCheckBox* m_checkPotentialProfit;
		wxCheckBox* m_checkPyServer;
		wxCheckBox* m_checkRandomBars;
		wxCheckBox* m_checkSingleThreadedAll;
		wxCheckBox* m_checkStatsSummary;
		wxCheckBox* m_checkTechUpdate;
		wxCheckBox* m_checkTrain;
		wxCheckBox* m_checkUseTicks;
		wxCheckBox* m_optimCostly;
		wxChoice* m_choiceMonthEndTF;
		wxChoice* m_choiceMonthStartTF;
		wxChoice* m_choiceYearEndTF;
		wxChoice* m_choiceYearStartTF;
		wxSpinCtrl* m_spinExperim1;
		wxSpinCtrl* m_spinExperim2;
		wxSpinCtrl* m_spinRandomPercent;
		wxSpinCtrl* m_spinRandomSeed;
		wxSpinCtrl* m_spinSLMulFilter;
		wxSpinCtrl* m_spinThreads;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		//*)

		ConfigTF2 m_confTF2;

	protected:

		//(*Identifiers(DialogTF)
		static const long ID_CHOICE5;
		static const long ID_CHOICE1;
		static const long ID_CHOICE2;
		static const long ID_CHOICE3;
		static const long ID_CHOICE4;
		static const long ID_CHECKBOX17;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX16;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX18;
		static const long ID_CHECKBOX20;
		static const long ID_CHECKBOX21;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL3;
		static const long ID_SPINCTRL4;
		static const long ID_CHECKBOX19;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL5;
		static const long ID_SPINCTRL6;
		//*)

	private:
        void ReadSelections();
        void RestoreConf();
        void Init();
        void UpdateChoicesForBools();
        void Gen2(wxWindow * parent, wxDialog * dialog, const EnjoLib::VecT<bool*> & bools, const EnjoLib::VecT<EnjoLib::Str> & boolsDescr, wxBoxSizer * sizer, MapCheckbox * mapCheckbox);//, wxObjectEventFunction* fun);

		//(*Handlers(DialogTF)
		void OnTF(wxCommandEvent& event);
		void Onm_spinSLMulFilterChange(wxSpinEvent& event);
		//*)

		MapChoiceEnum m_mapChoice;
		MapCheckbox m_mapCheckbox;
		MapSpin     m_mapSpin;
		std::vector<IMapControl *> m_maps;

		DECLARE_EVENT_TABLE()
};

#endif
