#include "Seasonal.h"
#include "IDataProvider.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "typesVec.h"

#include <Util/VecF.hpp>
#include <Util/CoutBuf.hpp>
#include <Statistical/Matrix.hpp>
#include <Statistical/Statistical.hpp>

#include <STD/VectorCpp.hpp>


using namespace EnjoLib;

const int Seasonal::PERIOD_SEASONAL = 24; /// TODO: Exclude Weekend! Iterate by date?

/*
Seasonal::Seasonal()
{
    //ctor
}

Seasonal::~Seasonal()
{
    //dtor
}
*/


VecF Seasonal::Run(const VecD & sig, int pred) const
{
    const int period = PERIOD_SEASONAL;
    //const int maxNumObs = 1; /// TODO: This is the original signal
    //const int maxNumObs = 50; /// TODO: This is already a model
    const int maxNumObs = m_averages;
    const Statistical stat;
    const VecCan & canVec = m_dat.GetCandles().GetDataVec();
    //Matrix obs(period);

    VecF ret;
    for (int i = 0; i < sig.size(); ++i)
    {
        if (i < period)
        {
            ret.Add(0);
        }
        else
        {
            const Candle & canThis = canVec.at(i);

            VecD obsV(period);
            for (int j = i - 1; j >= pred; j -= 1)
            //for (int j = i; j >= period; j -= period)
            {
                const Candle & canTest = canVec.at(j);
                if (not IsSeasonalCandle(canThis, canTest))
                {
                    continue;
                }
                //LOGL << "Found can = " << canTest.GetDateStr() << " for this " << canThis.GetDateStr() << Nl;
                const double diff = sig.at(j) - sig.at(j-pred);
                //const double diff = sig.at(j) - sig.at(j-period);
                const int idx = j % period;
                obsV.Add(diff);
                if (int(obsV.size()) >= maxNumObs)
                {
                    break;
                }
            }
            const double val = obsV.Mean();
            //const double val = stat.Median(obsV);
            ret.Add(val);
        }


    }
    //ret = sig;
    //LOGL << "Len ret = " << ret.Len() << ", sig = " << sig.Len() << Nl;
    return ret;
}

int Seasonal::FindOffsetToSeasonalCandle(int idxStart0, const VecCan & vecCan)
{
    const Candle & canThis = vecCan.at(idxStart0);
    for (int j = idxStart0 - 1; j >= 0; j -= 1)
    {
        const Candle & canTest = vecCan.at(j);
        if (not IsSeasonalCandle(canThis, canTest))
        {
            continue;
        }
        return j;
    }
    return -1;
}

bool Seasonal::IsSeasonalCandle(const Candle & canThis, const Candle & canTest)
{
    return canThis.GetHour() == canTest.GetHour();
}

VecF SeasonalModel::Run(const VecD & sig, int pred) const
{
    const VecF & base = Seasonal::Run(sig, pred);
    return base * m_averages * 0.7;
}

double SeasonalModel::PredictNext(const BufferDouble & datExpanding) const
{
    return Run(datExpanding.GetData()).Last();
}
unsigned SeasonalModel::GetLags() const
{
    return PERIOD_SEASONAL;
}


VecF SeasonalModel2::Run(const VecD & sig, int pred) const
{
    const int pers = Seasonal::PERIOD_SEASONAL;
    const VecF & base = m_model.Run(sig, pred);
    VecF ret(base.size(), 0);
    for (int i = pred; i < 2 ; ++i)
    {
        const float val = base[i];
        //ret.push_back(val);
    }
    for (int i = pers; i < base.size() - pred; ++i)
    {
        //const float val = base.at(i + pred);
        //ret.push_back(val);
    }

    for (int i = pers; i < base.size(); ++i)
    {
        if (i < base.size() - 1)
        {
                const float val = base.at(i - pers + 1);
                ret.at(i) = val;
        }
        else
        {
            const float val = base.at(i);
                //ret.push_back(val);
            ret.at(i) = val;
        }

    }
    //ret.pop_front();
    //ret.pop_back();
    //LOGL << "Seasonal2 = " << ret.Print();
    //ret = base;
    return ret;
}

double SeasonalModel2::PredictNext(const BufferDouble & datExpanding) const
{
    return Run(datExpanding.GetData()).Last();
}
unsigned SeasonalModel2::GetLags() const
{
    return Seasonal::PERIOD_SEASONAL - 1;
}

