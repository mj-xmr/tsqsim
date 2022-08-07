#include "OptiSubjectTSUtil.h"

#include "IOptimizable.h"
#include "OptiVar.h"
#include "OptiVarVec.h"

#include <Math/GeneralMath.hpp>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

OptiSubjectTSUtil::OptiSubjectTSUtil()
{
    //ctor
}

OptiSubjectTSUtil::~OptiSubjectTSUtil()
{
}

double OptiSubjectTSUtil::UpdateOptiGetPenality(const EnjoLib::FP * inp, int n, const EnjoLib::VecD & iterData, IOptimizable * opti) const
{
    EnjoLib::Array<OptiVarF *> vopti = opti->GetOptiFloat().Vec();
    //OptiVarF * varReal = FindVarCurrent(strat, iVar);
    double pentality = 0;
    //for (int iVar = 0; iVar < n; ++iVar),
    int iFloat = 0;
    int iInt = 0;
    for (unsigned iVar = 0; iVar < vopti.size(); ++iVar)
    //for (OptiVarF * varReal : vopti)
    {
        OptiVarF * varReal = vopti.at(iVar);
        if (not varReal->fp)
        {
            varReal->SetVal(iterData.at(iInt++));
        }
        else
        {
            float val = inp[iFloat++];
            //cout << "Val = " << iFloat << " = " << val << endl;
            double relErr = 0;
            const double min = varReal->valMin;
            const double max = varReal->valMax;
            if (val < min)
            {
                double diff = EnjoLib::GeneralMath().Fabs(val - min);
                relErr = diff / min;
            }

            if (val > max)
            {
                double diff = EnjoLib::GeneralMath().Fabs(val - max);
                relErr = diff / max;

            }
            if (relErr)
            {
                double pentalityCalc = EnjoLib::GeneralMath().PowInt(relErr, 2);
                pentality += pentalityCalc;
            }
            varReal->SetVal(val);
        }
    }
    return pentality;
}

EnjoLib::VecD OptiSubjectTSUtil::GetStartProt(const STDFWD::vector<OptiVarF> & optiVec) const
{
    EnjoLib::VecD ret;
    for (const OptiVarF & var : optiVec)
    {
        if (not var.fp)
            continue;
        //auto space = var.GetSpace();
        const double min = var.valMin;
        const double max = var.valMax;
        double mid = (min + max) / 2.0;
        ret.push_back(mid);
    }
    return ret.Data();
}
EnjoLib::VecD OptiSubjectTSUtil::GetStepProt(const STDFWD::vector<OptiVarF> & optiVec) const
{
    EnjoLib::VecD ret;
    for (const OptiVarF & var : optiVec)
    {
        if (not var.fp)
            continue;
        const double min = var.valMin;
        const double max = var.valMax;
        const double spacePercent = 0.1;
        double step = EnjoLib::GeneralMath().Fabs(max - min) * spacePercent;
        ret.push_back(step);
    }
    return ret.Data();
}
EnjoLib::Array<EnjoLib::OptiMultiSubject::Bounds> OptiSubjectTSUtil::GetBoundsProt(const STDFWD::vector<OptiVarF> & optiVec) const
{
    std::vector<OptiMultiSubject::Bounds> ret;
    for (const OptiVarF & var : optiVec)
    {
        if (not var.fp)
            continue;
        const double min = var.valMin;
        const double max = var.valMax;
        EnjoLib::OptiMultiSubject::Bounds b(min, max);
        ret.push_back(b);
    }
    return ret;
}
