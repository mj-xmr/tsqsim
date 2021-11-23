/***************************************************************
 * Name:      FuzzyCarriageApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#include "wx_pch.h"
#include "FuzzyCarriageApp.h"

//(*AppHeaders
#include "FuzzyCarriageMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FuzzyCarriageApp);

bool FuzzyCarriageApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    //wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	FuzzyCarriageFrame* Frame = new FuzzyCarriageFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
