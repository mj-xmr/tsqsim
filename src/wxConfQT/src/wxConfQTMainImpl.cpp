#include "wx_pch.h"
#include "wxConfQTMain.h"
#include "DialogPlots.h"
#include "DialogOpti.h"
#include "DialogTF.h"
#include "DialogML.h"
#include "DialogTS.h"
#include "wxUtil.h"

#include <MyChoiceEnum.h>
#include "EnumStringMapPlotType.h"
#include "EnumStringMapBufferType.h"
#include "EnumStringMapBufferVecType.h"
#include "EnumStringMapDataSrc.h"
#include <EnumStringMapStrat.h>
#include <TradeUtil.h>

#include <ConfigDirs.h>


using namespace EnjoLib;
using namespace std;

void wxConfQTFrame::Init()
{
    wxUtil wxu;
    wxu.InitYears(m_choiceYearStart);
    wxu.InitYears(m_choiceYearEnd);
    wxu.InitMonths(m_choiceMonthStart);
    wxu.InitMonths(m_choiceMonthEnd);

    m_choiceStrat->Init(EnumStringMapStrat()); // Linking errors
    m_choiceDataSrc->Init(EnumStringMapDataSrc());
    m_choicePlot->Init(EnumStringMapPlotType());
    m_choiceBuf1->Init(EnumStringMapBufferType());
    m_choiceBuf2->Init(EnumStringMapBufferType());
    m_choiceBuf3->Init(EnumStringMapBufferType());
    m_choiceBufRainbow->Init(EnumStringMapBufferVecType());

#ifndef WX_FULL
    //m_sizerQT->Hide(this, true);
    //m_sizerQT->Layout();
    m_choiceStrat->Hide();
    m_choicePlot->Hide();
    m_choiceBuf1->Hide();
    m_choiceBuf2->Hide();
    m_choiceBuf3->Hide();
    m_choiceBufRainbow->Hide();
    m_checkBigScreen->Hide();
    m_checkDirection->Hide();
    m_ckeckPltQT->Hide();
    m_butPlotDialog->Hide();
    m_txtBar->Hide();
    m_butClearBar->Hide();
    m_chkCache->Hide();
    m_butSigIdClear->Hide();
    m_txtSigId->Hide();
    m_butSigIdApply->Hide();
#endif
    InitSymbols();
    Read();
}

void wxConfQTFrame::Onm_choiceDataSrcSelect(wxCommandEvent& event)
{
    OnTF();
    InitSymbols();
    m_choiceSym->SetSelection(0);
    OnTF();
}

void wxConfQTFrame::InitSymbols()
{
    try {
        m_choiceSym->Clear();
        const VecStr & symbols = TradeUtil().GetAllSymbolsFromTxtDir();
        //wxMessageBox(wxString::Format("%d", symbols.size()));
        if (symbols.empty())
        {
            m_choiceSym->Append(_("Empty."));
        }
        else
        {
            for (const EnjoLib::Str & symbol : symbols)
            {
                //cout << "File = " << gcfgMan << endl;
                //wxMessageBox(symbol.c_str());
                m_choiceSym->Append(_(symbol.str()));
            }
        }

    }
    catch (exception & ex)
    {
        wxMessageBox(wxString::From8BitData(ex.what()), "Exception inside InitSymbols()!");
    }
}

bool wxConfQTFrame::MonthYearValidator()
{
    EnjoLib::Result<std::string> validRes = wxUtil().MonthYearValidator(m_choiceYearStart, m_choiceYearEnd, m_choiceMonthStart, m_choiceMonthEnd);
    m_status->SetStatusText(validRes.value.c_str());
    return validRes.isSuccess;
}

/// Store to config classes
void wxConfQTFrame::ReadSelections()
{
    /// TODO: Use Maps from EnjoLibWx
    wxUtil wxu;
    wxu.FromChoiceToLongInt(m_choiceYearStart,    &m_confSym.dates.yearStart);
    wxu.FromChoiceToLongInt(m_choiceYearEnd,      &m_confSym.dates.yearEnd);
    wxu.FromChoiceToLongInt(m_choiceMonthStart,   &m_confSym.dates.monthStart);
    wxu.FromChoiceToLongInt(m_choiceMonthEnd,     &m_confSym.dates.monthEnd);

    m_confSym.SetStrat(m_choiceStrat->GetSelection());
    m_confSym.SetDataSrc(m_choiceDataSrc->GetSelection());
    m_confSym.symbol.strRW() = m_choiceSym->GetString(m_choiceSym->GetCurrentSelection());
    m_confSym.period.strRW() = m_choicePeriod->GetString(m_choicePeriod->GetCurrentSelection());
    m_confSym.percentBars = m_sliderBars->GetValue();
    m_txtBar->GetValue().ToLong(&m_confSym.barNum);

    m_confQT.BIG_SCREEN = m_checkBigScreen->GetValue();
    m_confQT.DIRECTION = m_checkDirection->GetValue();
    //m_confQT.dateTime = std::string(m_txtSigId->GetValue().mb_str()); // mistake. Already handled
    m_confQT.buf1 = m_choiceBuf1->GetCurrentSelection();
    m_confQT.buf2 = m_choiceBuf2->GetCurrentSelection();
    m_confQT.buf3 = m_choiceBuf3->GetCurrentSelection();
    m_confQT.bufRainbow = m_choiceBufRainbow->GetCurrentSelection();

    m_confQT.PLOT_SIG_LAB = m_ckeckPltQT->GetValue();
    m_confQT.USE_CACHE = m_chkCache->GetValue();

    m_confTF.SIMUL_MULTITHREAD = m_checkSimulMT->GetValue();
    m_confTF.REPEAT = m_checkRepeat->GetValue();
    m_confTF.INDIVIDUAL_STRAT  = m_checkIndivStrat->GetValue();
    m_confTF.INDIVIDUAL_PERIOD = m_checkIndivPer->GetValue();
    m_confTF.INDIVIDUAL_SYMBOL = (int)m_checkIndivSym->Get3StateValue();
    m_confTF.PLOT_TYPE = m_choicePlot->GetCurrentSelection();
}

/// Populate selections
void wxConfQTFrame::RestoreConf()
{
    m_choiceStrat->SetSelection(0);
    if (m_confSym.GetStratInt() < m_choiceStrat->GetCount())
        m_choiceStrat->SetSelection(m_confSym.GetStratInt());
    m_choiceDataSrc->SetSelection(0);
    if (m_confSym.GetDataSrcInt() < m_choiceDataSrc->GetCount())
        m_choiceDataSrc->SetSelection(m_confSym.GetDataSrcInt());
    const wxUtil wxu;
    wxu.SetSelectionStr(m_choiceSym,        m_confSym.symbol.str(), true);
    wxu.SetSelectionStr(m_choicePeriod,     m_confSym.period.str());
    wxu.SetSelectionInt(m_choiceMonthStart, m_confSym.dates.monthStart);
    wxu.SetSelectionInt(m_choiceMonthEnd,   m_confSym.dates.monthEnd);
    wxu.SetSelectionInt(m_choiceYearStart,  m_confSym.dates.yearStart);
    wxu.SetSelectionInt(m_choiceYearEnd,    m_confSym.dates.yearEnd);


    m_checkBigScreen->SetValue(m_confQT.BIG_SCREEN);
    m_checkDirection->SetValue(m_confQT.DIRECTION);
    m_choiceBuf1->SetSelection(m_confQT.buf1);
    m_choiceBuf2->SetSelection(m_confQT.buf2);
    m_choiceBuf3->SetSelection(m_confQT.buf3);
    m_choiceBufRainbow->SetSelection(m_confQT.bufRainbow);

    m_ckeckPltQT->SetValue(m_confQT.PLOT_SIG_LAB);
    m_chkCache->SetValue(m_confQT.USE_CACHE);

    m_checkRepeat->     SetValue(m_confTF.REPEAT);
    m_checkSimulMT->    SetValue(m_confTF.SIMUL_MULTITHREAD);
    m_checkIndivStrat-> SetValue(m_confTF.INDIVIDUAL_STRAT);
    m_checkIndivPer->   SetValue(m_confTF.INDIVIDUAL_PERIOD);
    m_checkIndivSym->   Set3StateValue((wxCheckBoxState)m_confTF.INDIVIDUAL_SYMBOL);
    m_choicePlot->      SetSelection(m_confTF.PLOT_TYPE);
}

void wxConfQTFrame::GeneralHandler()
{
    if (!MonthYearValidator())
        return;
    ReadSelections();
    m_confSym.Write();
    m_confQT.Write();
    m_confTF.Write();
}

void wxConfQTFrame::Read()
{
    try
    {
        m_confSym.Read();
        m_confQT.Read();
        m_confTF.Read();

        RestoreConf();
    }
    catch (...)
    {
        wxMessageBox("Couldn't read conf");
    }
}

void wxConfQTFrame::Onm_butSigIdClearClick(wxCommandEvent& event)
{
    m_txtSigId->Clear();
    m_confQT.dateTime = "";
    GeneralHandler();
}

void wxConfQTFrame::Onm_butClearBarClick(wxCommandEvent& event)
{
    m_txtBar->SetValue("0");
    GeneralHandler();
}

void wxConfQTFrame::Onm_butPlotDialogClick(wxCommandEvent& event)
{
    DialogPlots * dlg = new DialogPlots(this);
    dlg->Show(true);
    //if (dlg.ShowModal() == wxID_OK)
    {
        //dlg.m_confQTPlot.Write();
        //wxMessageBox("OK");
    }
}

void wxConfQTFrame::Onm_butOptiDialogClick(wxCommandEvent& event)
{
    wxDialog * dlg = new DialogOpti(this);
    dlg->Show(true);
}

void wxConfQTFrame::Onm_butTF2DialogClick(wxCommandEvent& event)
{
    DialogTF * dlg = new DialogTF(this);
    dlg->Show(true);
}

void wxConfQTFrame::Onm_butMLDialogClick(wxCommandEvent& event)
{
    DialogML * dlg = new DialogML(this);
    dlg->Show(true);
}

void wxConfQTFrame::Onm_butTSClick(wxCommandEvent& event)
{
    wxDialog * dlg = new DialogTS(this);
    dlg->Show(true);
}

