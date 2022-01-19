#include "wx_pch.h"
#include "DialogTS.h"
#include "wxUtil.h"
#include "PredictorTypeStr.h"
#include "PredictorType.h"
#include "PriceTypeStr.h"
#include "PriceType.h"

#include <UtilWx.hpp>
#include <Template/SafePtr.hpp>

void DialogTS::OnTS(wxCommandEvent& event)
{
    ReadSelections();
    m_confTS.Write(); // OK not needed
}

void DialogTS::Init()
{
    /*
    m_mapCheckbox.Register(&m_confQTPlot.CANDLES,           m_chkCandles);
    m_mapCheckbox.Register(&m_confQTPlot.TECHS,             m_chkTechs);
    */
    m_choicePredType  ->Init(PredictorTypeStr(),    int(PredictorType::PRED_AR));
    m_choiceSeriesType->Init(PriceTypeStr(),        int(PriceType::HIGH));

    m_mapChoice.Register(&m_confTS.PRED_TYPE,  m_choicePredType);
    m_mapChoice.Register(&m_confTS.PRICE_TYPE, m_choiceSeriesType);

    m_maps.push_back(&m_mapChoice);
    m_maps.push_back(&m_mapCheckbox);
}

/// Store to config classes
void DialogTS::ReadSelections()
{
    for (IMapControl * pmap : m_maps)
        pmap->FromCheckToVariable();
    m_confTS.m_scriptPathTxt    = m_txtScriptPath->   GetValue().c_str().AsChar();
    m_confTS.m_scriptPathTxtR   = m_txtScriptPathR->  GetValue().c_str().AsChar();
    m_confTS.m_scriptPathTxtGen = m_txtScriptPathGen->GetValue().c_str().AsChar();
}

/// Populate selections
void DialogTS::RestoreConf()
{
    m_confTS.Read();

    wxUtil().AutoGenCheckBox(this, m_confTS, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogTS::OnTS);
    m_txtScriptPath   ->SetValue(m_confTS.m_scriptPathTxt.   c_str());
    m_txtScriptPathR  ->SetValue(m_confTS.m_scriptPathTxtR.  c_str());
    m_txtScriptPathGen->SetValue(m_confTS.m_scriptPathTxtGen.c_str());

    for (IMapControl * pmap : m_maps)
        pmap->FromVariableToCheck();
}

void DialogTS::Onm_butScriptTextClick(wxCommandEvent& event)
{
    EnjoLib::UtilWx::FindFileFillTxt(this, m_txtScriptPath);
    OnTS(event);
}

void DialogTS::Onm_butScriptTextOpenClick(wxCommandEvent& event)
{
    const wxString file_name = m_txtScriptPath->GetValue();
    EnjoLib::UtilWx::ExecuteDefaultEditorOnFile(file_name, ".txt");
}


void DialogTS::Onm_butScriptTextRClick(wxCommandEvent& event)
{
    EnjoLib::UtilWx::FindFileFillTxt(this, m_txtScriptPathR);
    OnTS(event);
}

void DialogTS::Onm_butScriptTextOpenRClick(wxCommandEvent& event)
{
    const wxString file_name = m_txtScriptPathR->GetValue();
    EnjoLib::UtilWx::ExecuteDefaultEditorOnFile(file_name, ".txt");
}

void DialogTS::Onm_butScriptTextGenClick(wxCommandEvent& event)
{
    EnjoLib::UtilWx::FindFileFillTxt(this, m_txtScriptPathGen);
    OnTS(event);
}

void DialogTS::Onm_butScriptTextOpenGenClick(wxCommandEvent& event)
{
    const wxString file_name = m_txtScriptPathGen->GetValue();
    EnjoLib::UtilWx::ExecuteDefaultEditorOnFile(file_name, ".txt");
}
