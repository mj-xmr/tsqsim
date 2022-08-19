#include "IModel.h"
#include "IDataProvider.h"
#include "IPeriod.h"
#include "RFEType.h"
#include "RDEType.h"
#include "DTWDistType.h"
#include "ConfigMan.h"
#include "ConfigML.h"
#include "Factories.h"
#include "Buffer.h"
#include "BufferVecType.h"
#include "BufferVecUpdateable.h"
#include <Util/VecF.hpp>
#include <Math/GeneralMath.hpp>
#include <Statistical/EigenFactoryAbstract.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

IModel::~IModel(){}
IModel::IModel(const IPeriod & per, const Factories & fact)
: m_per(per)
, m_fact(fact)
, m_eigen(fact.GetEigen().Create(EIGENTYPE_DEFAULT))
{}

const IDataProvider & IModel::GetPer() const
{
    return m_per;
}

const EnjoLib::EigenAbstract & IModel::GetEigen() const
{
    return *m_eigen;
}

void IModel::SetLenTechs(int lenTechs)
{
    if (lenTechs > 0)
        m_lenTechsOverride = lenTechs;
}

int IModel::GetNumCVs() const
{
    return gcfgMan.cfgML->ML_NUM_CVS;
}

bool IModel::IS_INVERTED_BARS() const
{
    return gcfgMan.cfgML->ML_INV_BARS;
}

bool IModel::IsPricePercent() const
{
    return false;
    return true;
}

bool IModel::IsPriceCorrected() const
{
    return false;
    return true;
}

bool IModel::IsFilterByMedian() const
{
    //return true;
    return false;
}

int IModel::GetLenTechsOverride() const
{
    return m_lenTechsOverride;
}

float IModel::GetPCAQuality() const
{
    return gcfgMan.cfgML->GetPCAQuality();
}

int IModel::GetPCANumberFeatures() const
{
    return gcfgMan.cfgML->PCA_NUM;
}

DTWDistType IModel::GetDisttype() const
{
    return gcfgMan.cfgML->GetDistType();
}

RFEType IModel::GetRFEtype() const
{
    return gcfgMan.cfgML->GetRFEType();
}

RDEType IModel::GetRDEtype() const
{
    return gcfgMan.cfgML->GetRDEType();
}

void IModel::AddTech(int sti, EnjoLib::VecD * columns, const BufferType & type) const
{
    Buffer buf = m_per.GetBuf(type);
    columns->Add(buf[sti]);
}

void IModel::AddTechVec(int sti, EnjoLib::VecD * columns, const BufferVecType & type, const Transform & trx) const
{
    for (const auto & data : m_per.GetBufVec(type.GetType()))
    {
        Buffer buf(data);
        const float raw = buf[sti];
        const float valTrx = (raw + trx.add) * trx.mul;
        //cout << "Raw = " << raw << " valTrx = " << valTrx << endl;
        columns->Add(valTrx);
    }
}

void IModel::AddTechVecDiffs(int sti, EnjoLib::VecD * columns, const BufferVecType & type) const
{
    const GeneralMath gmat;
    for (const auto & data : m_per.GetBufVec(type.GetType()))
    {
        Buffer buf(data);
        const double curr = buf[sti];
        const double prev = buf[sti + 1];
        const double relat = gmat.RelativeChange(curr, prev);
        const double absol = gmat.AbsoluteChange(curr, prev);
        const double change = IsPricePercent() ? relat : absol;
        columns->Add(change);
    }
}
