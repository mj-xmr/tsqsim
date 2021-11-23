/***************************************************************
 * Name:      FuzzyCarriageApp.h
 * Purpose:   Defines Application Class
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef FUZZYCARRIAGEAPP_H
#define FUZZYCARRIAGEAPP_H

#ifndef WX_PRECOMP
  #include <wx/app.h>
#endif

class FuzzyCarriageApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // FUZZYCARRIAGEAPP_H
