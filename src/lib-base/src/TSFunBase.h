#ifndef TSFUNBASE_H
#define TSFUNBASE_H

#include "ITSFun.h"
#include "TSRes.h"
#include "TSInput.h"

class IPeriod;
class IDataProvider;
class IBufferCandles;
class Candle;

class TSFunBase : public ITSFun
{
    public:
        TSFunBase(const TSInput & tsin);
        virtual ~TSFunBase();

        TSRes OnDataPoint(int idx) const override final;
        unsigned Len() const override final;

        const TSInput & GetTSIn() const;
        const IPeriod & GetPer() const;
        const IDataProvider & GetData() const;
        const IBufferCandles & GetCandles() const;
        Candle GetCandle(int idx, int shift = 0) const;

    protected:

        virtual TSRes OnDataPointProt(int idx) const = 0;
        virtual unsigned LenProt() const;       /// TODO remove
        /// virtual unsigned MaxShift() const; /// TODO Implement like in the ITSXForm
        virtual bool CrashOnWarning() const;

        unsigned LenData() const;

    private:

        const TSInput & m_tsin;
        const IPeriod & m_per;
        const IBufferCandles & m_bufCan;
};

#endif // TSFUNBASE_H
