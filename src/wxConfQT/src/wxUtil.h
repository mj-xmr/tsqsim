#ifndef WXUTIL_H
#define WXUTIL_H

#include <Util/Result.hpp>
#include <3rdParty/stdfwd.hh>

class wxChoice;
class wxString;
class MapCheckbox;
class IConfig;
class wxUtil
{
    public:
        wxUtil(){}
        virtual ~wxUtil(){}

        EnjoLib::Result<std::string> MonthYearValidator(wxChoice * yearStart, wxChoice * yearEnd, wxChoice * monthStart, wxChoice * monthEnd) const;
        void SetSelectionStr(wxChoice* choice, const wxString & sel, bool ignoreErrors = false) const;
        void SetSelectionInt(wxChoice* choice, long int sel) const;
        void InitYears(wxChoice* choice) const;
        void InitMonths(wxChoice* choice) const;
        void InitChoice(wxChoice* choice, int start, int end) const;
        void FromChoiceToLongInt(const wxChoice* choice, long int * out) const;
        void AutoGenCheckBox(wxWindow * dialog, const IConfig & cfg, wxBoxSizer * sizer, MapCheckbox * mapCheckbox, wxObjectEventFunction fun) const;

    protected:

    private:
};

#endif // WXUTIL_H
