#include "wx_pch.h"
#include "DialogOpti.h"
#include "EnumStringMapOptiType.h"
#include "OptiType.h"
#include "OptiGoalType.h"

#include "wxUtil.h"

#include <Util/CharManipulations.hpp>

#include <wx/spinctrl.h>

using namespace std;

void DialogOpti::OnOpti(wxCommandEvent& event)
{
    ReactWrite();
}

void DialogOpti::OnSpin(wxSpinEvent& event)
{
    ReactWrite();
}

void DialogOpti::React()
{
    ReadSelections();
    UpdateDayLabels();
}

void DialogOpti::ReactWrite()
{
    cout << "Writing\n";
    React();
    m_confOpti.Write(); // OK not needed
}

void DialogOpti::UpdateDayLabels()
{
    const int daysOpti = m_confOpti.OPTI_CROSS_VALID_BARS_OPTI_H1   / 24;
    const int daysXVal = m_confOpti.OPTI_CROSS_VALID_BARS_XVAL      / 100.0 * daysOpti;

    m_labDaysOpti->SetLabel(EnjoLib::CharManipulations().ToStr(daysOpti).c_str());
    m_labDaysXVal->SetLabel(EnjoLib::CharManipulations().ToStr(daysXVal).c_str());
}

void DialogOpti::Init()
{
    m_choiceOpti        ->Init(EnumStringMapOptiType(),     int(OptiType::OPTI_TYPE_NONE));
    m_choiceOptiMethod  ->Init(EnumStringMapOptiMethod(),   int(OptiMethod::OPTI_METHOD_GRID));
    m_choiceOptiGoal    ->Init(EnumStringMapOptiGoalType(), int(OptiGoalType::SUM));

    m_mapChoice.Register(&m_confOpti.OPTIMIZER, m_choiceOpti);
    m_mapChoice.Register(&m_confOpti.OPTIMIZER_METHOD, m_choiceOptiMethod);
    m_mapChoice.Register(&m_confOpti.OPTIMIZER_GOAL, m_choiceOptiGoal);

    /*
    m_mapCheckbox.Register(&m_confOpti.OPTI_VERBOSE,         m_checkVerbose);
    */
    
    m_mapSpin.Register(&m_confOpti.OPTI_CROSS_VALID_BARS_OPTI_H1,   m_spinNumBarsOpti);
    m_mapSpin.Register(&m_confOpti.OPTI_CROSS_VALID_BARS_XVAL,      m_spinPercent4XValid);
    m_mapSpin.Register(&m_confOpti.OPTI_RANDOM_SAMPLES_NUM,         m_spinRandomSamples);
    m_mapSpin.Register(&m_confOpti.OPTI_RANDOM_MIN_DIFF_PROMILE,    m_spinMaxESPromile);
    
    m_maps.push_back(&m_mapChoice);
    m_maps.push_back(&m_mapSpin);
    m_maps.push_back(&m_mapCheckbox);

    //RestoreConf(); // Trying AutoGen
    React();
}

/// Store to config classes
void DialogOpti::ReadSelections()
{
    for (IMapControl * pmap : m_maps)
        pmap->FromCheckToVariable();
}

/// Populate selections
void DialogOpti::RestoreConf()
{
    m_confOpti.Read();
    wxUtil().AutoGenCheckBox(this, m_confOpti, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogOpti::OnOpti);
    m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);
    for (IMapControl * pmap : m_maps)
        pmap->FromVariableToCheck();
}
