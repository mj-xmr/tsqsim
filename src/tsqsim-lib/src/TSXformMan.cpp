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

TSRes TSXformMan::OnDataPointProt(const IHasCandles & funBase, int idx) const
{
    TSRes res(true);
    double conv = 0;
    for (const CorPtr<ITSXform> & pxform : m_xforms)
    {
        const XformRes & val = pxform->Run(funBase, m_priceType, idx, conv);
        conv = val.conv;
        res.lost.Add(val.lost);
        /// TODO: 2) Collect a VecD of lost info for each xform individually
    }
    res.val = conv;
    return res;
}

TSRes TSXformMan::Reconstruct(double val, const EnjoLib::VecD & valLostVec) const
{
    bool verbose = true;
    verbose = false;
    for (int i = int(m_xforms.size() - 1); i >= 0; --i)
    {   // Iterate the transformations in the reverse order w.r.t. as they were applied
        const CorPtr<ITSXform> & pxform = m_xforms.at(i);

        const int idxMin = pxform->MaxShift();

        //if (idx - idxMin < 0)
        {
          //  val = 0;
            //continue;
        }

        VecD vecIn;
        //for (int j = idx; j >= idx - idxMin; --j)
        {
            //if (j < 0)
            {
              //  vecIn.Add(input.at(0)); /// TODO: use lost
            }
            //else
            {
                //vecIn.Add(input.at(j));
            }

        }
        //const VecD & inVecLost = lost.at(idx);
        //vecIn.Add(inVecLost.at(0));
        //vecIn.Add(input.at(idx));
        vecIn.Add(val);

        const double valLost = valLostVec.at(i);

        val = pxform->Invert(vecIn, valLost);
        if (verbose)
        {
            //LOGL << idx << ":\txf = " << i << ", in = " << vecIn.Print() << ", out = " << val << Nl;
        }
    }
    if (verbose)
    {
        //LOGL << Nl;
    }

    TSRes res(true);
    res.val = val;
    return res;
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
