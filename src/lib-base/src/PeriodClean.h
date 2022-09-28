#ifndef PERIODCLEAN_H
#define PERIODCLEAN_H

#include "IPeriod.h"
#include "SRDummy.h"
#include "PriceFilterConfig.h"
#include "MaPeriods.h"
#include "DataOCHL.h"
#include "Tick.h"
#include "Leverages.h"
#include "Candle.h"
#include "BufferCandles.h"
#include "PeriodType.h"

#include <Util/Pimpl.hpp>
#include <Util/Str.hpp>
#include <Template/CacheRAMBase.hpp>

class BufferVecUpdateable;
class PriceFilterType;

class PeriodClean : public IPeriod
{
    public:
        PeriodClean(const PeriodType & type, const ISymbol & sym);
        virtual ~PeriodClean(){}

        void Feed(const EnjoLib::IIterableConst<Tick> & tick, bool updateTech) override;
        void Feed(const Tick & tick, bool update = false) override;
        void FeedFromLower(const Tick & tick, int periodRatio) override;
        void CalcTech() override;
        void UpdateTech() override;
        void FinalizeCandle() override;
        void LimitData(int maxLatestBars) override;
        void FilterPrice(const PriceFilterConfig & cfg) override;
        PriceFilterConfig GetPriceFilterConfigGlob() const override {return m_priceFilterCfg;}
        void SetPriceFilterConfig(const PriceFilterConfig & cfg) override { m_priceFilterCfg = cfg;}
        //void SetMaUsed(int period) const;
        //int GetMaUsedPeriodSlow() const;
        //int GetMaUsedPeriodFast() const;
        //bool IsMaUsedPeriodSlowMax() const;
        int GetNumTicks() const override;
        int GetNumSeconds() const override;

        // IDataProvider
        DataOCHL GetData(int numBack, int n = 0) const override;
        DataTech GetTech(int numBack, int n = 0) const override;
        DataOCHL GetDataDate(DateInt dateStart, int n) const override;
        DataTech GetTechDate(DateInt dateStart, int n) const override;
        // IDataProvider end

        DateInt GetDateStart(int numBack) const override;
        DateInt GetDateEnd(int numBack, int n = 0) const override;
        EnjoLib::Str GetName() const override;
        EnjoLib::Str GetSymbolName() const override { return m_symbolName; }
        EnjoLib::Str GetSymbolPeriodId(char delim = '-') const override;
        bool IsMetaTrader() const override;
        float GetSpread(int sti) const override;
        float GetLeverage() const override;
        virtual float GetTPRatio() const override {return 3;}
        //virtual float GetTPRatio() const {return 100;};
        virtual float GetMaxLossPercent() const override { return 0.01; };
        bool UsingTicks() const override { return m_usingTicks; }

        Buffer GetBuf(const BufferType & type) const override;
        BufferBool GetBufBool(const BufferTypeBool & type) const override;
        const EnjoLib::Array<EnjoLib::VecF> & GetBufVec(const BufferVecType & type) const override;

        //Buffer GetADXR() const override {return m_adxr; };
        //Buffer GetMaUsedSlow() const;
        //Buffer GetMaUsedFast() const;
        virtual EnjoLib::View<MaPeriods> GetMaUsedPeriods() const override;// { return m_maPeriods; };
        Buffer GetMa(int period) const override;
        const IBufferCandles & GetCandles() const override;
        float GetClose(int i) const override;
        //Buffer GetOpensNext() const override { return Buffer(m_opensNext); }
        //BufferCandles GetCandles2() const override;
        //BufferCandles GetCandles4() const override;
        //BufferCandles GetCandles8() const override;
        virtual const ISR & GetSR() const override { return m_srDummy; };
        virtual const SRVisibleData & GetSRVisible(Direction dir) const override;
        //const Abstracts & GetAbstracts() const { return m_abstr; };

        void SetCandles(const VecCan & candles) override;
        void SetCandles(const STDFWD::deque<Candle> & candles) override;
        void SetCandles(const STDFWD::deque<Tick> & candles) override;
        //void SetStates(const HmmStates & states) override { m_hmmStatesData = states; };
        int Len() const override;

        const DataOCHL & GetDataFull() const override { return m_data; }
    protected:
        DataOCHL m_data;
        //VecCan m_candles;
        const VecCanView & CanData() const;
        VecCan & CanData();

    private:
        void FilterPricePriv(const PriceFilterConfig & cfg, const PriceFilterType & type);
        void FinalizeCandlePriv(bool updateTech = false);

        PriceFilterConfig m_priceFilterCfg;
        PeriodType m_type;
        bool m_usingTicks = false;
        SRDummy m_srDummy;
        //SRVisibleData m_srVisDummy;
        int m_numTicks = 0;
        int m_currTick = 0;
        int m_minutePrev = -1;
        int m_hourPrev = -1;
        int m_dayPrev = -1;
        
        EnjoLib::Str m_symbolName;
        Leverages m_leverages;
        Candle m_currCandle;
        Tick m_tickMod;

        //BufferCandles m_bufCan;



        mutable EnjoLib::CacheRAMBasePtr<int, EnjoLib::VecF> m_mas;

        PIMPL
};

#endif // PERIODCLEAN_H
