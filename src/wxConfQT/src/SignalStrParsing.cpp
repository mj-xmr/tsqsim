#include "wx_pch.h"
#include "wxConfQTMain.h"
#include "wxUtil.h"
#include <TradeUtil.h>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>




using namespace std;
using namespace EnjoLib;

// Expected format:
// NZDUSD_h1_2017_08_22__04_00
void wxConfQTFrame::Onm_butSigIdApplyClick(wxCommandEvent& event)
{
    try
    {
        std::string c = std::string(m_txtSigId->GetValue().mb_str());
        if (c.find('|') != string::npos)
        {
            try
            {
                c = TradeUtil().LabelLineToUnderscoresWXid(c).str();
            }
            catch(exception & ex)
            {
                wxMessageBox(wxString::Format("Error at trade util = %s", ex.what()));
                return;
            }

        }

        VecStr tokens = Tokenizer().Tokenize(c, '_');
        wxString symbol, period, year, month;
        int i = 0;
        try
        {
            symbol =    wxString(tokens.at(i++).c_str());
            period =    wxString(tokens.at(i++).c_str());
            year =      wxString(tokens.at(i++).c_str());
            month =     wxString(tokens.at(i++).c_str());

            symbol = symbol.Upper();
            period = period.Lower();
            if (month.at(0) == '0')
                month = month.at(1);
        }
        catch(exception & ex)
        {
            wxMessageBox(wxString::Format("Error at index = %d", i));
            return;
        }
        Str strM = tokens.at(3);
        int m;
        try
        {
            m = CharManipulations().ToInt(strM);
        }
        catch(exception & ex)
        {
            wxMessageBox(wxString::Format("Error at CharManipulations().ToInt(strM). Input = %s", strM.c_str()));
            return;
        }
        //int mStart = m-1;
        int mEnd = m+1;
        int mStart = m;
        //int mEnd = m;
        if (mStart < 1) mStart = 1;
        if (mEnd > 12) mEnd = 12;

        wxUtil wxu;
        wxu.SetSelectionStr(m_choiceSym, symbol);
        wxu.SetSelectionStr(m_choicePeriod, period);
        wxu.SetSelectionStr(m_choiceMonthStart, wxString::Format("%i", mStart));
        wxu.SetSelectionStr(m_choiceMonthEnd, wxString::Format("%i", mEnd));
        wxu.SetSelectionStr(m_choiceYearStart, year);
        wxu.SetSelectionStr(m_choiceYearEnd, year);
        m_confQT.dateTime = c;

        GeneralHandler();

        wxExecute("../multi-tf-qt/run-kill.sh");
        m_txtSigId->Clear(); // ?
    }
    catch(exception & ex)
    {
        wxMessageBox(wxString::Format("Unhandled exception %s", ex.what()));
        return;
    }
}
