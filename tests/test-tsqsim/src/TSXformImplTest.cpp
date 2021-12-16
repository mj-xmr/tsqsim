#include "pch_test.h"


#include "TSXformFactory.h"
#include "TSXformType.h"
#include "TSXformTypeString.h"

#include <Util/CoutBuf.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace EnjoLib;
TEST(Conv_Log)
{   
    TSXformTypeString xform2str;
    const TSXformType type = TSXformType::LOGS;
    const Str xformStr = xform2str.at(int(type));
    CorPtr<ITSXform> xform = TSXformFactory().Create(xformStr);
    
    CHECK_CLOSE(-xform->Run(VecD(1, 1.5)), xform->Run(VecD(1, 0.5)), 0.01);
}

TEST(Conv_inv)
{
    bool verbose = false;
    //verbose = true;
    VecD inp;
    inp.Add(-11);
    inp.Add(-2);
    inp.Add(-0.5);
    inp.Add(0);
    inp.Add(0.5);
    inp.Add(1);
    inp.Add(1.5);
    inp.Add(10);
    TSXformTypeString xform2str;
    for (int itype = 0; itype < int(TSXformType::END); ++itype)
    {
        const TSXformType type = TSXformType(itype);
        const Str xformStr = xform2str.at(itype);
        if (verbose)
        {
            LOGL << xformStr << Nl;
        }
        if (type == TSXformType::ADD)
        {
            /// TODO: Uses a different constructor
            continue;
        }
        CorPtr<ITSXform> xform = TSXformFactory().Create(xformStr);
        
        switch (type)
        {
            /// TODO: Service exceptions
        case TSXformType::DIFF:
            break;        /// TODO: Probably the most important
        case TSXformType::FABS:
            break;
        case TSXformType::ADD:
            break;
        default:
            {
                for (int i = 0; i < int(inp.size()); ++i)
                {
                    const double valIn = inp.at(i);
                    const double res = xform->Run(   VecD(1, valIn));
                    const double inv = xform->Invert(VecD(1, res));
                    if (verbose)
                    {
                        LOGL << "in = " << valIn << ", res = " << res << ", inv = " << inv << Nl;
                    }
                    CHECK_CLOSE(valIn, inv, 0.01);
                }
                
            }
        }
    }
}

TEST(Conv_diffs)
{
    /// TODO: TSXformType::DIFF:
}

TEST(Conv_add)
{
    /// TODO: TSXformType::ADD:
}