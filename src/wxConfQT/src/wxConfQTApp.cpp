/***************************************************************
 * Name:      wxConfQTApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2015-08-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wxConfQTApp.h"

//(*AppHeaders
#include "src/wxConfQTMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxConfQTApp);

bool wxConfQTApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    // wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxConfQTFrame* Frame = new wxConfQTFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
