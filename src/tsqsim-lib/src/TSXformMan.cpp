#include "TSXformMan.h"

#include "TSRes.h"
#include "TSXformFactory.h"
#include "TSXformRes.h"

#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
#include <Math/MaxMinFindF.hpp>
//#include <Util/CharManipulations.hpp>
#include <Template/CorradePointer.h>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;

TSXformMan::~TSXformMan(){}
TSXformMan::TSXformMan(const PriceType & priceType)
: m_priceType(priceType)
{
    const TSXformFactory fact;
    AddXForm("orig");
    Assertions::IsFalse(m_xforms.empty(), "TSXformMan::TSXformMan");
}

void TSXformMan::AddXForm(const EnjoLib::Str & namePars)
{
    const TSXformFactory fact;
    m_xforms.push_back(fact.Create(namePars));
}
void TSXformMan::AddXForm(const TSXformType & type, const VecStr & params)
{
    const TSXformFactory fact;
    m_xforms.push_back(fact.CreateByType(type, params));
}

void TSXformMan::AddXForm(ITSXform * xform)
{
    m_xforms.push_back(CorPtr<ITSXform>(xform));
}

TSRes TSXformMan::OnDataPointProt(const IHasCandles & funBase, int idx) const
{
    TSRes res(true);
    double conv = ITSXform::DATA_INITIAL;
    for (const CorPtr<ITSXform> & pxform : m_xforms)
    {
        const XformRes & val = pxform->Run(funBase, m_priceType, idx, conv);
        conv = val.conv;
        res.lost.Add(val.lost);
        /// TODO: 2) Collect a VecD of lost info for each xform individually
    }
    res.val = conv;
    //LOGL << " TSXformMan::OnDataPointProt res.val = " << res.val << Nl;
    return res;
}

VecD TSXformMan::ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const
{
    bool verbose = true;
    verbose = false;

    VecD ret;
    if (verbose)
    {
        LOGL << "ReconstructVec input = " << input.Print() << Nl;
    }

    double valPrev = 0;
    for (int j = 0; j < input.size(); ++j)
    {
    double val = input.at(j);
    const VecD & valLostVec = lost.at(j);
    for (int i = int(m_xforms.size() - 1); i >= 0; --i)
    {   // Iterate the transformations in the reverse order w.r.t. as they were applied
        const CorPtr<ITSXform> & pxform = m_xforms.at(i);

        VecD vecIn;
        vecIn.Add(val);
        vecIn.Add(valPrev); // Add lost?

        const double valLost = valLostVec.at(i);

        val = pxform->Invert(vecIn, valLost);
        if (verbose)
        {
            LOGL << i << ", j = " << j << ", in = " << vecIn.Print() << ", lost = " << valLost << ", out = " << val << Nl;
        }
    }
    ret.Add(val);
    valPrev = val;
    }
    return ret;
}

unsigned TSXformMan::MaxShift() const
{
    MaxMinFindF mmf;
    unsigned shift = 0;
    for (const auto & pxform : m_xforms)
    {
        const unsigned maxShift = pxform->MaxShift();
        mmf.UpdateMax(maxShift);
    }
    if (mmf.IsMaxValid())
    {
        shift = mmf.GetMax();
    }
    return shift;
}
