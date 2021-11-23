/***************************************************************
 * Name:      FuzzyCarriageMain.h
 * Purpose:   Defines Application Frame
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef FUZZYCARRIAGEMAIN_H
#define FUZZYCARRIAGEMAIN_H

#ifndef WX_PRECOMP
//(*Headers(FuzzyCarriageFrame)
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/choice.h>
//*)
#endif

#include "Carriage.h"

class MyTimer;
class myScrolledWindow;

class FuzzyCarriageFrame: public wxFrame
{
    public:

        FuzzyCarriageFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FuzzyCarriageFrame();
        void SetSliderVel( double velPercent );
        void SetSliderPos( double posPercent );

    private:

        //(*Handlers(FuzzyCarriageFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Onm_butStartClick(wxCommandEvent& event);
        void Onm_butStopClick(wxCommandEvent& event);
        void Onm_slVelCmdScrollChanged(wxScrollEvent& event);
        void Onm_slPosCmdScrollChanged(wxScrollEvent& event);
        void Onm_chkControlClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(FuzzyCarriageFrame)
        static const long ID_SCROLLEDWINDOW1;
        static const long ID_SLIDER1;
        static const long ID_SLIDER2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_CHOICE1;
        static const long ID_CHECKBOX1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FuzzyCarriageFrame)
        wxCheckBox* m_chkControl;
        wxPanel* Panel1;
        wxChoice* m_choiceTime;
        wxSlider* m_slVel;
        wxStatusBar* StatusBar1;
        wxButton* m_butStop;
        myScrolledWindow* m_scrWin;
        wxSlider* m_slPos;
        wxButton* m_butStart;
        //*)

        MyTimer * m_timer;
        Carriage m_carriage;

        DECLARE_EVENT_TABLE()
};

#endif // FUZZYCARRIAGEMAIN_H
