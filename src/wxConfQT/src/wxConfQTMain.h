/***************************************************************
 * Name:      wxConfQTMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2015-08-19
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WXCONFQTMAIN_H
#define WXCONFQTMAIN_H
#include <ConfigSym.h>
#include <ConfigQT.h>
#include <ConfigTF.h>

//(*Headers(wxConfQTFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
class MyChoiceEnum;
class wxConfQTFrame: public wxFrame
{
    public:

        wxConfQTFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxConfQTFrame();

    private:
        ConfigSym m_confSym;
        ConfigQT m_confQT;
        ConfigTF m_confTF;

        void Init();
        void InitSymbols();
        void Read();
        bool MonthYearValidator();
        void ReadSelections();
        void RestoreConf();
        void GeneralHandler();
        void OnTF();

        //(*Handlers(wxConfQTFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Onm_choiceYearStartSelect(wxCommandEvent& event);
        void Onm_sliderBarsCmdScrollThumbRelease(wxScrollEvent& event);
        void Onm_butLoadClick(wxCommandEvent& event);
        void On_TF(wxCommandEvent& event);
        void On_QT(wxCommandEvent& event);
        void Onm_butSigIdClearClick(wxCommandEvent& event);
        void Onm_butSigIdApplyClick(wxCommandEvent& event);
        void Onm_butClearBarClick(wxCommandEvent& event);
        void On_General(wxCommandEvent& event);
        void Onm_butPlotDialogClick(wxCommandEvent& event);
        void Onm_butOptiDialogClick(wxCommandEvent& event);
        void Onm_butTF2DialogClick(wxCommandEvent& event);
        void Onm_butMLDialogClick(wxCommandEvent& event);
        void Onm_butTSClick(wxCommandEvent& event);
        void Onm_choiceDataSrcSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxConfQTFrame)
        static const long ID_CHOICE7;
        static const long ID_CHOICE13;
        static const long ID_CHOICE1;
        static const long ID_CHOICE2;
        static const long ID_CHOICE3;
        static const long ID_CHOICE4;
        static const long ID_CHECKBOX1;
        static const long ID_CHOICE5;
        static const long ID_CHOICE6;
        static const long ID_SLIDER1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON5;
        static const long ID_CHECKBOX13;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX7;
        static const long ID_BUTTON6;
        static const long ID_CHOICE9;
        static const long ID_CHOICE10;
        static const long ID_CHOICE11;
        static const long ID_CHOICE12;
        static const long ID_CHECKBOX11;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX4;
        static const long ID_BUTTON8;
        static const long ID_BUTTON7;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_BUTTON3;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON4;
        static const long ID_CHOICE8;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX8;
        static const long ID_BUTTON2;
        static const long ID_BUTTON1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wxConfQTFrame)
        MyChoiceEnum* m_choiceBuf1;
        MyChoiceEnum* m_choiceBuf2;
        MyChoiceEnum* m_choiceBuf3;
        MyChoiceEnum* m_choiceBufRainbow;
        MyChoiceEnum* m_choiceDataSrc;
        MyChoiceEnum* m_choicePlot;
        MyChoiceEnum* m_choiceStrat;
        wxButton* m_butClearBar;
        wxButton* m_butLoad;
        wxButton* m_butMLDialog;
        wxButton* m_butOptiDialog;
        wxButton* m_butPlotDialog;
        wxButton* m_butSave;
        wxButton* m_butSigIdApply;
        wxButton* m_butSigIdClear;
        wxButton* m_butTF2Dialog;
        wxButton* m_butTS;
        wxCheckBox* m_checkBigScreen;
        wxCheckBox* m_checkDirection;
        wxCheckBox* m_checkIndivPer;
        wxCheckBox* m_checkIndivStrat;
        wxCheckBox* m_checkIndivSym;
        wxCheckBox* m_checkRepeat;
        wxCheckBox* m_checkSimulMT;
        wxCheckBox* m_chkCache;
        wxCheckBox* m_chkYearsTogether;
        wxCheckBox* m_ckeckPltQT;
        wxChoice* m_choiceMonthEnd;
        wxChoice* m_choiceMonthStart;
        MyChoiceEnum* m_choicePeriod;
        wxChoice* m_choiceSym;
        wxChoice* m_choiceYearEnd;
        wxChoice* m_choiceYearStart;
        wxSlider* m_sliderBars;
        wxStaticBoxSizer* m_sizerQT;
        wxStatusBar* m_status;
        wxTextCtrl* m_txtBar;
        wxTextCtrl* m_txtSigId;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXCONFQTMAIN_H
