#include "wx_pch.h"
#include "wxUtil.h"
#include "Consts.h"
#include "TradeUtil.h"
#include "IConfig.h"

#include <Autogen/AutoGenCheckBox.hpp>
#include <Ios/Osstream.hpp>

EnjoLib::Result<std::string> wxUtil::MonthYearValidator(wxChoice * yearStart, wxChoice * yearEnd, wxChoice * monthStart, wxChoice * monthEnd) const
{
    int selYStart = yearStart->GetCurrentSelection();
    int selYEnd = yearEnd->GetCurrentSelection();
    int selStart = monthStart->GetCurrentSelection();
    int selEnd = monthEnd->GetCurrentSelection();

    if (selYStart > selYEnd)
    {
        //m_status->SetStatusText("Year smaller");
        //return EnjoLib::Result<std::string>("Year smaller", false);
        yearStart->SetSelection(selYEnd);
    }

    if (selYStart == selYEnd && selStart > selEnd)
    {
        monthStart->SetSelection(selEnd);
        //return EnjoLib::Result<std::string>("Month smaller", false);
    }

    //m_status->SetStatusText();
    return EnjoLib::Result<std::string>("==== OK! ====", true);
}

void wxUtil::SetSelectionStr(wxChoice* choice, const wxString & sel, bool ignoreErrors) const
{
    int pos = choice->FindString(sel);
    if (pos < 0)
    {
        if (ignoreErrors)
        {
            choice->SetSelection(0);
            return;
        }
        else
        {
            wxMessageBox("wxUtil::SetSelectionStr(wxChoice* choice) - Not found selection - " + sel);
            return;
        }
    }
    choice->SetSelection(pos);
}

void wxUtil::SetSelectionInt(wxChoice* choice, long int sel) const
{
    EnjoLib::Osstream oss;
    oss << sel;
    return SetSelectionStr(choice, oss.str().str());
}

void wxUtil::InitYears(wxChoice* choice) const
{
    InitChoice(choice, 2000, TradeUtil().GetYearMonthMax().first);
}
void wxUtil::InitMonths(wxChoice* choice) const
{
    //InitChoice(choice, 1, TradeUtil().GetYearMonthMax().second);
    InitChoice(choice, 1, 12);
}

void wxUtil::InitChoice(wxChoice* choice, int start, int end) const
{
    choice->Clear();
    for (int i = start; i <= end; ++i)
    {
        EnjoLib::Osstream oss;
        oss << i;
        choice->Append(oss.str().c_str());
    }
    choice->SetSelection(0);
}

void wxUtil::FromChoiceToLongInt(const wxChoice* choice, long int * out) const
{
    int selStart = choice->GetCurrentSelection();
    choice->GetString(selStart).ToLong(out);
}

void wxUtil::AutoGenCheckBox(wxWindow * dialog, const IConfig & cfg, wxBoxSizer * sizer, MapCheckbox * mapCheckbox, wxObjectEventFunction fun) const
{
    const EnjoLib::VecT<bool*> & bools              = cfg.GetBools();
    const EnjoLib::VecT<EnjoLib::Str> & boolsDescr  = cfg.GetBoolsDescr();
    const EnjoLib::VecT<EnjoLib::Str> & boolsToolt  = cfg.GetBoolsToolTip();

    EnjoLib::AutoGenCheckBox::Gen(dialog, bools, boolsDescr, boolsToolt, sizer, mapCheckbox, fun);
}
