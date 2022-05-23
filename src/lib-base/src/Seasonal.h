#ifndef SEASONAL_H
#define SEASONAL_H

#include "PredictorBase.h"

/*
class Seasonal
{
    public:
        Seasonal();
        virtual ~Seasonal();

    protected:

    private:
};
*/
class Seasonal
{
public:
    Seasonal(const IDataProvider & dat, int averages = 1)
    : m_averages(averages)
    , m_dat(dat)
    {}
    virtual ~Seasonal(){}

    virtual EnjoLib::VecF Run(const EnjoLib::VecD & sig, int pred = 1) const;

    static int FindOffsetToSeasonalCandle(int idxStart0, const VecCan & vecCan);
    static bool IsSeasonalCandle(const Candle & canThis, const Candle & canTest);
    static const int PERIOD_SEASONAL;
protected:
    int m_averages = 1;
    const IDataProvider & m_dat;
};

class SeasonalModel : public Seasonal, public PredictorBase
{
    public:
    SeasonalModel(const IDataProvider & dat, int averages)
    : Seasonal(dat, averages)
    , PredictorBase(dat, "SeasonalH1")
    {}
    virtual ~SeasonalModel(){}

    double PredictNext(const BufferDouble & datExpanding) const override;
    unsigned GetLags() const override;

    EnjoLib::VecF Run(const EnjoLib::VecD & sig, int pred = 1) const override;
};

class SeasonalModel2 : public PredictorBase
{
    public:
    SeasonalModel2(const IDataProvider & dat, const SeasonalModel & model)
    : PredictorBase(dat, "SeasonalH1")
    , m_model(model)
    , m_dat(dat)
    {}
    virtual ~SeasonalModel2(){}

    const SeasonalModel & m_model;
    const IDataProvider & m_dat;

    double PredictNext(const BufferDouble & datExpanding) const override;
    unsigned GetLags() const override;

    EnjoLib::VecF Run(const EnjoLib::VecD & sig, int pred = 1) const;
};


#endif // SEASONAL_H
