#include "wx_pch.h"
#include "DialogML.h"
#include "EnumStringMapRFEType.hpp"
#include "EnumStringMapRDEType.hpp"
#include "EnumStringMapDistType.hpp"
#include "RFEType.h"
#include "RDEType.h"
#include "DTWDistType.h"
#include "wxUtil.h"

void DialogML::Init()
{
    m_choiceRFEType ->Init(EnumStringMapRFEType(),  int(RFEType::RFE_PCA_OPTI));
    m_choiceRDEType ->Init(EnumStringMapRDEType(),  int(RDEType::RDE_AUTO));
    m_choiceDistType->Init(EnumStringMapDistType(), int(DTWDistType::KNNType));

    m_mapChoice.Register(&m_confML.RFE_TYPE,  m_choiceRFEType);
    m_mapChoice.Register(&m_confML.RDE_TYPE,  m_choiceRDEType);
    m_mapChoice.Register(&m_confML.DIST_TYPE, m_choiceDistType);

    m_mapSpin.Register(&m_confML.PCA_QUAL,      m_spinPCA);
    m_mapSpin.Register(&m_confML.PCA_NUM,       m_spinPCANum);
    m_mapSpin.Register(&m_confML.LEN_TECHS,     m_lenTechs);
    m_mapSpin.Register(&m_confML.LEN_TECHS_MIN, m_spinLenTechsMin);
    m_mapSpin.Register(&m_confML.LEN_TECHS_MAX, m_spinLenTechsMax);
    m_mapSpin.Register(&m_confML.VERBOSITY,     m_spinVerbosity);
    m_mapSpin.Register(&m_confML.ML_NUM_CVS,    m_spinKFolds);

    /*
    m_mapCheckbox.Register(&m_confML.ML_INV_BARS,       m_checkAddInverseBars);
    m_mapCheckbox.Register(&m_confML.ML_FIND_HORI,      m_checkFindHori);
    m_mapCheckbox.Register(&m_confML.ML_USE_RELEASE,    m_checkRelease);
    m_mapCheckbox.Register(&m_confML.ML_REM_ERRATIC,    m_checkRemErratic);
    m_mapCheckbox.Register(&m_confML.ML_REUSE_PCA,      m_checkReusePCA);
    */

    m_maps.push_back(&m_mapChoice);
    m_maps.push_back(&m_mapSpin);
    m_maps.push_back(&m_mapCheckbox);

    RestoreConf();
}

// Store to config classes
void DialogML::ReadSelections()
{
    for (IMapControl * pmap : m_maps)
        pmap->FromCheckToVariable();
}

/// DialogML selections
void DialogML::RestoreConf()
{
    m_confML.Read();
    wxUtil().AutoGenCheckBox(this, m_confML, m_sizerBools, &m_mapCheckbox, (wxObjectEventFunction)&DialogML::OnML);
    m_sizerTop->Fit(this);
	m_sizerTop->SetSizeHints(this);
    for (IMapControl * pmap : m_maps)
        pmap->FromVariableToCheck();
}

void DialogML::OnML(wxCommandEvent& event)
{
    ReadSelections();
    m_confML.Write(); // OK not needed
}

void DialogML::OnSpin(wxSpinEvent& event)
{
    ReadSelections();
    m_confML.Write(); // OK not needed
}
