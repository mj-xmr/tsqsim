/***************************************************************
 * Name:      wx_pch.h
 * Purpose:   Header to create Pre-Compiled Header (PCH)
 * Author:     ()
 * Created:   2015-08-19
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WX_PCH_H_INCLUDED
#define WX_PCH_H_INCLUDED

// basic wxWidgets headers
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#ifdef WX_PRECOMP
    // put here all your rarely-changing header files
    #include <wx/wx.h>
    #include <wx/app.h>
    #include <wx/msgdlg.h>
    #include <wx/valnum.h>
   // #include <wx/image.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/menu.h>
    #include <wx/slider.h>
    #include <wx/statusbr.h>
    #include <wx/frame.h>
    #include <wx/textctrl.h>
    #include <wx/choice.h>
    #include <wx/valnum.h>
    #include <wx/spinctrl.h>
#endif // WX_PRECOMP

#endif // WX_PCH_H_INCLUDED
