#include "wx_pch.h"
#include "EnumStringMapSimulType.h"
#include "SimulatorType.h"
#include "DialogTF.h"
#include "wxUtil.h"
#include <wx/spinctrl.h>

#include <Statistical/Assertions.hpp>
#include <Util/ThreadWrap.hpp>
#include <Util/Pair.hpp>

void DialogTF::Init()
{
    wxUtil wxu;
    wxu.InitYears(m_choiceYearStartTF);
    wxu.InitYears(m_choiceYearEndTF);
    wxu.InitMonths(m_choiceMonthStartTF);
    wxu.InitMonths(m_choiceMonthEndTF);

    m_choiceSim->Init(EnumStringMapSimulType(), int(SimulatorType::SIMUL_STANDARD));

    m_spinThreads->SetRange(0, EnjoLib::ThreadWrap::GetConcurrency() * 2);

    m_mapChoice.Register(&m_confTF2.MT_SIM_TYPE, m_choiceSim);

    m_mapSpin.Register(&m_confTF2.THREADS, m_spinThreads);
    m_mapSpin.Register(&m_confTF2.RANDOM_BARS_PERCENT,  m_spinRandomPercent);
    m_mapSpin.Register(&m_confTF2.RANDOM_BARS_SEED,     m_spinRandomSeed);
    m_mapSpin.Register(&m_confTF2.SPREAD_MUL_FILTER,    m_spinSLMulFilter);
    m_mapSpin.Register(&m_confTF2.EXPERIM_INT_1,        m_spinExperim1);
    m_mapSpin.Register(&m_confTF2.EXPERIM_INT_2,        m_spinExperim2);

    //m_mapCheckbox.Register(&m_confTF2.SINGLE_THREADED_ALL,  m_checkSingleThreadedAll);
    //m_mapCheckbox.Register(&m_confTF2.STATS_SUMMARY,        m_checkStatsSummary);

    m_maps.push_back(&m_mapChoice);
    m_maps.push_back(&m_mapSpin);
    m_maps.push_back(&m_mapCheckbox);

    RestoreConf();

    m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);
}

/// Store to config classes
void DialogTF::ReadSelections()
{
    m_confTF2.PLOTS = (int)m_checkPlots->Get3StateValue();

    for (IMapControl * pmap : m_maps)
        pmap->FromCheckToVariable();

    const wxUtil wxu;
    wxu.MonthYearValidator(m_choiceYearStartTF, m_choiceYearEndTF, m_choiceMonthStartTF, m_choiceMonthEndTF);
    UpdateChoicesForBools();
}

void DialogTF::UpdateChoicesForBools()
{
    const wxUtil wxu;
    using PairChoices = EnjoLib::Pair<wxChoice*, long*>;
    std::vector<PairChoices> dateChoices;
    dateChoices.push_back(PairChoices(m_choiceYearStartTF,  &m_confTF2.dates.yearStart));
    dateChoices.push_back(PairChoices(m_choiceYearEndTF,    &m_confTF2.dates.yearEnd));
    dateChoices.push_back(PairChoices(m_choiceMonthStartTF, &m_confTF2.dates.monthStart));
    dateChoices.push_back(PairChoices(m_choiceMonthEndTF,   &m_confTF2.dates.monthEnd));

    for (auto & pairC : dateChoices)
    {
        wxChoice* control = pairC.first;
        wxu.FromChoiceToLongInt(control, pairC.second);
        control->Enable(m_confTF2.CUSTOM_DATE);
    }

    using PairWinBool = EnjoLib::Pair<wxWindow*, bool>;
    std::vector<PairWinBool> winBools;
    winBools.push_back(PairWinBool(m_spinSLMulFilter,   m_confTF2.FILTER_PRICE));
    winBools.push_back(PairWinBool(m_spinRandomPercent, m_confTF2.RANDOM_BARS));
    winBools.push_back(PairWinBool(m_spinRandomSeed,    m_confTF2.RANDOM_BARS));

    for (auto & pairC : winBools)
    {
        wxWindow* control = pairC.first;
        control->Enable(pairC.second);
    }
}

/// DialogTF selections
void DialogTF::RestoreConf()
{
    m_confTF2.Read();
    // This has to be after Read in order to work
    wxUtil().AutoGenCheckBox(this, m_confTF2, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogTF::OnTF);

    m_checkPlots->Set3StateValue((wxCheckBoxState)m_confTF2.PLOTS);

    for (IMapControl * pmap : m_maps)
        pmap->FromVariableToCheck();

    const wxUtil wxu;
    wxu.SetSelectionInt(m_choiceMonthStartTF,  m_confTF2.dates.monthStart);
    wxu.SetSelectionInt(m_choiceMonthEndTF,    m_confTF2.dates.monthEnd);
    wxu.SetSelectionInt(m_choiceYearStartTF,   m_confTF2.dates.yearStart);
    wxu.SetSelectionInt(m_choiceYearEndTF,     m_confTF2.dates.yearEnd);

    UpdateChoicesForBools();
}

void DialogTF::Onm_spinSLMulFilterChange(wxSpinEvent& event)
{
    ReadSelections();
    m_confTF2.Write(); // OK not needed
}

void DialogTF::OnTF(wxCommandEvent& event)
{
    ReadSelections();
    m_confTF2.Write(); // OK not needed
}
