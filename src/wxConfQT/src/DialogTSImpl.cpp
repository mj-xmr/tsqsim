#include "wx_pch.h"
#include "DialogTS.h"
#include "wxUtil.h"
#include "PredictorTypeStr.h"
#include "PredictorType.h"

#include <Template/SafePtr.hpp>

#include <wx/mimetype.h>

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
    m_choicePredType->Init(PredictorTypeStr(), int(PredictorType::PRED_AR));
    
    m_mapChoice.Register(&m_confTS.PRED_TYPE, m_choicePredType);
    
    m_maps.push_back(&m_mapChoice);
    m_maps.push_back(&m_mapCheckbox);
}

/// Store to config classes
void DialogTS::ReadSelections()
{
    for (IMapControl * pmap : m_maps)
        pmap->FromCheckToVariable();
    m_confTS.m_scriptPathTxt = m_txtScriptPath->GetValue().c_str().AsChar();
}

/// Populate selections
void DialogTS::RestoreConf()
{
    m_confTS.Read();

    wxUtil().AutoGenCheckBox(this, m_confTS, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogTS::OnTS);
    m_txtScriptPath->SetValue(m_confTS.m_scriptPathTxt.c_str());
    
    for (IMapControl * pmap : m_maps)
        pmap->FromVariableToCheck();
}

void DialogTS::Onm_butScriptTextClick(wxCommandEvent& event)
{
    const wxString & fil = m_txtScriptPath->GetValue();

    wxFileDialog openFileDialog(this, _("Save " + fil), "", fil,  "", wxFD_PREVIEW);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_txtScriptPath->SetValue(openFileDialog.GetPath());
    OnTS(event);
}

void DialogTS::Onm_butScriptTextOpenClick(wxCommandEvent& event)
{
    const wxString file_name = m_txtScriptPath->GetValue();

    // 1) Get File Type
    EnjoLib::SafePtr<wxFileType> c_type(wxTheMimeTypesManager->GetFileTypeFromExtension(".txt"));
    if(!c_type.IsValid())
    {
        wxMessageBox("Couldnt find asosiation");
        return;
    }

    // 2) Get Open Message
    const wxString command = c_type->GetOpenCommand(file_name);
    if(!command)
    {
        wxMessageBox("No default program");
        return; //No defoult program
    }
    // 3) Execute message
    wxExecute(command);
}
