#include "CrossValidCalc.h"
#include "IHasLen.h"
#include "ConfigOpti.h"

#include <Statistical/Assertions.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Except.hpp>


using namespace std;
using namespace EnjoLib;

CrossValidCalc::CrossValidCalc(int totallen, int numBarsOpti, float percentAhead, bool isLast)
: m_totallen(totallen)
, m_numBarsOpti(numBarsOpti)
, m_numBarsAhead(numBarsOpti * percentAhead)
{
    if (numBarsOpti <= 0)
    {
        throw EnjoLib::ExceptInvalidArg("CrossValidCalc() numBarsOpti == " + EnjoLib::CharManipulations().ToStr(numBarsOpti));
    }
    if (percentAhead <= 0 && not isLast)
    {
        throw EnjoLib::ExceptInvalidArg("CrossValidCalc() percentAhead == " + EnjoLib::CharManipulations().ToStr(percentAhead));
    }
    Assertions().IsTrue(m_numBarsOpti < m_totallen, ("CrossValidCalc() m_numBarsOpti " + EnjoLib::CharManipulations().ToStr(m_numBarsOpti) + " <  m_totallen " + EnjoLib::CharManipulations().ToStr(m_totallen)).c_str());
    //cout << "CrossValidCalc()\nm_totallen = " << m_totallen << ", m_numBarsOpti = " << m_numBarsOpti << ", m_numBarsAhead = " << m_numBarsAhead << endl;
}

CrossValidCalc::CrossValidCalc(const IHasLen & len, const IPeriod & per, const ConfigOpti & confOpti)
: CrossValidCalc(len.Len(),
                 confOpti.GetOPTI_CROSS_VALID_BARS_OPTI(per),
                 confOpti.GetOPTI_CROSS_VALID_BARS_XVAL(per),
                 confOpti.OPTI_LAST
                 )
{}

CrossValidCalc::~CrossValidCalc(){}

OptiXValid CrossValidCalc::GetPass(int i) const
{
    const OptiXValid & retThis = GetPassPriv(i);
    if (i > 0)
    {
        const OptiXValid & retPrev = GetPassPriv(i-1);
        if (retThis == retPrev)
        {
            throw EnjoLib::ExceptLogicError("CrossValidCalc::GetPass(): the same OptiXValid");
        }
    }

    return retThis;
}

OptiXValid CrossValidCalc::GetPassPriv(int i) const
{
    OptiXValid ret;
    if (i < 0)
    {
        ret.opti.start = m_totallen - m_numBarsAhead - m_numBarsOpti;
        ret.opti.end   = m_totallen - m_numBarsAhead;

        ret.xvalid.start = m_totallen - m_numBarsAhead;
        ret.xvalid.end   = m_totallen - 1;
    }
    else
    {
        ret.opti.start = m_numBarsAhead * i;
        ret.opti.end   = m_numBarsOpti + m_numBarsAhead * i;

        ret.xvalid.start = m_numBarsOpti + m_numBarsAhead * (i);
        ret.xvalid.end   = m_numBarsOpti + m_numBarsAhead * (i+1);
    }

    ret.isValid = ret.xvalid.end < m_totallen;

    return ret;
}

OptiXValid CrossValidCalc::GetPassLast() const
{
    return GetPass(-1);
}

StartEnd OptiXValid::GetBoth() const
{
    return StartEnd(opti.start, xvalid.end);
}

bool OptiXValid::operator== (const OptiXValid & other) const
{
    return opti == other.opti && xvalid == other.xvalid;
}

StartEnd CrossValidCalc::GetUpToNumber(int progress) const
{
    StartEnd ret(progress - m_numBarsOpti, progress);
    return ret;
}

