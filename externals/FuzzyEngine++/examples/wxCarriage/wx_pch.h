/***************************************************************
 * Name:      wx_pch.h
 * Purpose:   Header to create Pre-Compiled Header (PCH)
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
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
  #include <wx/string.h>
  #include <wx/intl.h>
  #include <wx/msgdlg.h>
  #include <wx/menu.h>
  #include <wx/statusbr.h>
  #include <wx/frame.h>
  #include <wx/dcbuffer.h>
#endif // WX_PRECOMP

#endif // WX_PCH_H_INCLUDED
