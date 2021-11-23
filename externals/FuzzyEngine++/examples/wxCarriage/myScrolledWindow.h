/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef _canvas_h
#define _canvas_h
#include <vector>
using namespace std;

#ifndef WX_PRECOMP
	#include <wx/scrolwin.h>
#endif

class wxWindow;
//class Carriage;

class myScrolledWindow: public wxScrolledWindow
{
public:
    myScrolledWindow(wxWindow * parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style , const wxString& name);
    virtual ~myScrolledWindow();

    void UpdateCarriage( const Carriage & carriage, double force );

protected:
    virtual void OnDraw (wxDC& dc);

    wxColor bgCol;
    DECLARE_EVENT_TABLE()

    Carriage m_carriage;
    double m_force;
};

#endif
