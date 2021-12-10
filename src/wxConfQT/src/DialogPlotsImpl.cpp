#include "wx_pch.h"
#include "DialogPlots.h"
#include "wxUtil.h"

void DialogPlots::OnQTPlot(wxCommandEvent& event)
{
    ReadSelections();
    m_confQTPlot.Write(); // OK not needed
}

void DialogPlots::Init()
{
    /*
    m_mapCheckbox.Register(&m_confQTPlot.CANDLES,           m_chkCandles);
    m_mapCheckbox.Register(&m_confQTPlot.TECHS,             m_chkTechs);
    m_mapCheckbox.Register(&m_confQTPlot.SIGNAL_TRADE,      m_chkSigTrade);
    m_mapCheckbox.Register(&m_confQTPlot.SIGNAL_SPECIAL,    m_chkSigSpec);
    m_mapCheckbox.Register(&m_confQTPlot.PROFIT,            m_chkProfit);
    m_mapCheckbox.Register(&m_confQTPlot.SIMUL,             m_chkSimul);
    m_mapCheckbox.Register(&m_confQTPlot.SL,    m_chkSL);
    m_mapCheckbox.Register(&m_confQTPlot.TPS,   m_chkTPs);
    m_mapCheckbox.Register(&m_confQTPlot.MA,    m_chkMA);
    m_mapCheckbox.Register(&m_confQTPlot.SR,    m_chkSR);
    m_mapCheckbox.Register(&m_confQTPlot.SR_GROUPS, m_chkSRgroups);
    m_mapCheckbox.Register(&m_confQTPlot.STD_DEV,   m_chkStdDev);
    m_mapCheckbox.Register(&m_confQTPlot.DAY_WEEK,  m_chkWknd);
    m_mapCheckbox.Register(&m_confQTPlot.BET,       m_checkBet);
    m_mapCheckbox.Register(&m_confQTPlot.DARK,      m_chkDark);
    m_mapCheckbox.Register(&m_confQTPlot.ZIG_ZAG,   m_chkZigZag);
    m_mapCheckbox.Register(&m_confQTPlot.ZIG_ZAG_INDEXES, m_chkZZidx);
    */
}

/// Store to config classes
void DialogPlots::ReadSelections()
{
    m_mapCheckbox.FromCheckToVariable();
}

/// Populate selections
void DialogPlots::RestoreConf()
{
    m_confQTPlot.Read();
    
    wxUtil().AutoGenCheckBox(this, m_confQTPlot, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogPlots::OnQTPlot);

    m_mapCheckbox.FromVariableToCheck();
}
