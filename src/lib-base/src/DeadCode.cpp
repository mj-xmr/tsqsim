#include "DeadCode.h"

DeadCode::DeadCode()
{
    //ctor
}

DeadCode::~DeadCode()
{
    //dtor
}

/*
float OrderMarket::GetCapMultiplier() const
{
    float divisor = GetCapNumerator() / float(GetCapDivisor());
    return divisor;
}

void OrderMarket::IncrementCapDivisorLockProfit(DateInt closeDate)
{
    const Candle & openCandle = m_period->GetCandles().GetCandle(closeDate);
    const float openPrice = openCandle.GetOpen();
    float prevCapMul = GetCapMultiplier();
    // Calculate partial profit
    ++m_capDivisor;
    float profitPartial = CalcPartialProfit(openPrice, prevCapMul);
    m_profitPartial += profitPartial;
}

void OrderMarket::GiveBackCapNumeratorLockProfit(DateInt closeDate)
{
    if (GetCapNumerator() == 1)
        throw ExceptInvalidArg("OrderMarket::GiveBackCapNumeratorLockProfit() Numerator is already = 1");

    const Candle & openCandle = m_period->GetCandles().GetCandle(closeDate);
    const float openPrice = openCandle.GetOpen();
    float prevCapMul = GetCapMultiplier();
    m_capNumerator = 1; // Give back the numerator
    float profitPartial = CalcPartialProfit(openPrice, prevCapMul);
    m_profitPartial += profitPartial;
}

float OrderMarket::CalcPartialProfit(float candleOpenPrice, float prevCapMultiplier) const
{
    float currCapMul = GetCapMultiplier();
    float diffCapMul = prevCapMultiplier - currCapMul; // Ta zmienna stanowi wlasnie zamkniety kapital
    float profitPartialAbs = candleOpenPrice - m_open;
    if (!m_dir)
        profitPartialAbs = -profitPartialAbs;
    float profitPartial = profitPartialAbs * diffCapMul;
    return profitPartial;
}


float OrderMarket::GetProfitAbsPartialCorrected() const
{
    float partial = GetProfitAbs() - m_profitPartial;
    return partial;
}

float OrderMarket::GetProfitProcPartialCorrected() const
{
    float partial = GetProfitAbsPartialCorrected();
    float profitProc = partial / m_open * m_capMultiplierInitial;
    return profitProc;
}

        //void IncrementCapDivisorLockProfit(DateInt closeDate);
        //void GiveBackCapNumeratorLockProfit(DateInt closeDate);
        //float GetProfitAbsPartialCorrected() const;
        //float GetProfitProcPartialCorrected() const;
*/

/*
bool ISignal::HandleCache(const State & st, std::map<unsigned, bool> & cache) const
{
    auto it = cache.find(st.i);
    if (it == cache.end())
    {
        bool val = IsSignalProt(st);
        cache[st.i] = val;
        return val;
    }

    return cache[st.i];
}

bool ISignal::HandleCacheLinear(const State & st, std::vector<Bool3State> & cache) const
{
    if (cache.empty())
        cache = std::vector<Bool3State>(Len());
    Bool3State & b = cache[st.i];
    if (b.GetVal() == Bool3State::UNDEF)
    {
        bool val = IsSignalProt(st);
        b.SetVal(val);
        return val;
    }
    return b.GetVal() == Bool3State::TRUE;
}


float CapCalc::GetCapSecure(float maxLossPercent, float slOpen, float open) const
{
    const float maxCap = gcfg.MAX_CAP;
    if (!gcfg.CAP_SECURE)
        return maxCap;

    float spread = m_per.GetSpread(st.i);
    float loss = (EnjoLib::GeneralMath().Fabs(slOpen - open) + spread) / open;
    float maxLoss = maxLossPercent / 100.0;
    float expectedLeverage;
    if (loss > maxLoss)
      expectedLeverage = 0;
    else
      expectedLeverage = maxLoss / loss;

    float currMaxLeverage = AccountLeverage(); // TODO: Variable for commodities!
    //float expectedLeverage = 35;
    float percentOfMargin = expectedLeverage / currMaxLeverage;

    if (percentOfMargin > maxCap)
    {
        percentOfMargin = maxCap;
    }
    return percentOfMargin;
}

*/


// StrategyRetrace
/*
const int MAX_DIST_ARMED_OUTSIDE_RANGE = 15;
    const int MAX_DIST_ARMED_INSIDE_RANGE = 50;
    const int MIN_DIST_ARMED_INSIDE_RANGE = 6;
if (not IsSigStoch(st))
    {
        //return false;
    }
    if (Logic::GT(m_indAggrSlowD.GetValue(st.i), 50, st))
    {
        //return false;
    }

    if (m_stochFit[st] > 70)
    {
        //return false;
    }

    if (m_trendnessSmooth[st] == -TaLib::TRENDNESS_MAX)
    {
        //return false;
    }

    if (lastPosSeriesInv > 0)
    {
        if (lastPosSeriesInv < lastPosSeriesThis)
        {
            //return false;
        }
        //if (not AlgoRetraceCompare::IsFirstStronger(m_indiOneDirCandleSeries, st.Shift(lastPosSeriesThis), st.Shift(lastPosSeriesInv).Invert()))
        {
            //return false;
        }
    }

    //if (not AlgoRetraceCompare::IsFallStronger(m_bufCandles, m_indiOneDirCandleSeries, st.Shift(lastPosSeriesThis), st))
    {
        //return false;
    }
    //if (lastPosSeriesInv > 0)
    {
      //  if (lastPosSeriesThis > lastPosSeriesInv)
        {
            //log << __PRETTY_FUNCTION__ << ", " << lastPosSeriesThis << ", " << lastPosSeriesInv << endl;
            //return false; // Use only first signal in this direction
        }
    }
    //if (IsTooManyStochExtremes(st, lastPosSeriesThis))
    {
        //return false;
    }

    int diff = lastPosSeriesThis - st.i;

    // If in range
    if (not st.bullish)
    {
        //log << "lo, hi = " << cRange.GetLow() << ", " << cRange.GetHigh() << endl;
    }

    if (not m_indiRetrace.IsSignal(st))
    {
        if (st.bullish)
        {
  //          log << "Not retracement signal" << endl;
        }
        //return false;
    }

    //cout << st.bullish << ", " << st.i << " , stdDev = " << stdDev[st.i] << " diff = " << diff << endl;
    if (cRange.GetLow() <= close && close <= cRange.GetHigh() )
    {
        //ASSERT_TRUE_OR_RET_FALSE(diff > MAX_DIST_ARMED_INSIDE_RANGE);
        if (diff > MAX_DIST_ARMED_INSIDE_RANGE)
        {
            //return false;
        }
        if (diff < MIN_DIST_ARMED_INSIDE_RANGE)
        {
            //return false;
        }

    }
    else // outside range
    {
        //return false;
        //ASSERT_TRUE_OR_RET_FALSE(diff > MAX_DIST_ARMED_OUTSIDE_RANGE);
        if (diff < MAX_DIST_ARMED_INSIDE_RANGE)
        {
            //return false;
        }
        if (diff > MAX_DIST_ARMED_OUTSIDE_RANGE)
        {
            //return false;
        }
    }
    if (IsLastSRBreached(st, cRange))
    {
        //return false;
    }

    //int lpi = m_indAggrSlowD.GetPosLastSignal(st.Next().Invert());
    //int lp  = m_indAggrSlowD.GetPosLastSignal(st.Shift(lpi));


   // if (lpi < lp)
        //if (lp < lastPosSeriesThis)
        {
            //return false;
        }
*/

/*
    int lastPosSeriesThis = m_indiOneDirCandleSeriesEMA.GetPosLastSignal(st);
    if (lastPosSeriesThis < 0)
    {
        return false;
    }

    const State stlastPosSeriesThis = st.Shift(lastPosSeriesThis);

    int lastPosSeriesInv  = m_indiOneDirCandleSeries.GetPosLastSignal(stlastPosSeriesThis.Invert());
    if (lastPosSeriesInv < 0)
    {
        return false;
    }

    const State stlastPosSeriesInv = st.Shift(lastPosSeriesInv).Invert();
    const Candle & cRange = m_indiOneDirCandleSeries.GetRange(stlastPosSeriesThis);
    const Candle & cRangeInv = m_indiOneDirCandleSeries.GetRange(stlastPosSeriesInv);
    float lenThis = cRange.GetLen();
    float lenInv = cRangeInv.GetLen();
    if (cRange.GetLen() < cRangeInv.GetLen() * MUL_REL_LEN) // Too small range, compared to previous inverse
    {
        if (m_cc.IsInCandle(cRangeInv, close))
        {
            //const State stThisEnd = m_indiOneDirCandleSeries.GetPosSignalEnd(lastPosSeriesThis);
            //const State stInvStart = m_indiOneDirCandleSeries.GetPosSignalStart(stlastPosSeriesInv);
            if (st.bullish)
            {
                if (cRange.GetHigh() < cRangeInv.GetHigh())
                {
                    return false; // Failed to make higher high
                }
            }
            else
            {
                if (cRange.GetLow() > cRangeInv.GetLow())
                {
                    return false; // Failed to make lower low
                }
            }
        }
    }
    */
    /*
    const PairInt minMax = m_cc.GetMinMaxSlowFract(stlastPosSeriesThis, st, m_indiFract);
    const int extrInt = st.bullish ? minMax.one : minMax.two;
    const float extr = m_indiFract.GetValue(st.Shift(extrInt));
    const float len = EnjoLib::GeneralMath().Fabs(close - extr);
    if (len < cRange.GetLen())
    {
        return false;
    }
    */

    /*
    const State st1dStart = m_indiOneDirCandleSeries.GetPosSignalStart(st.Shift(lastPosSeriesThis));
    const State st1dEnd =   m_indiOneDirCandleSeries.GetPosSignalEnd(st.Shift(lastPosSeriesThis));
    const std::vector<SRFinal> & vsr = m_patPinbarSR.GetLevels(st);
    for (const SRFinal & sr : vsr)
    {
        int srStart = sr.GetStart();
        int st1dStarti = st1dStart.i;
        int st1dEndi = st1dEnd.i;
        if (st1dStarti >= srStart && srStart >= st1dEndi - 1)
        {
            // OK
        }
        else
        {
            return false; // At least one broken SR didn't belong to the retracement in question
        }
    }

    const SRClusteringInterpr srClustInt;
    std::vector<EnjoLib::KMeans1dCluster> clust = srClustInt.ReduceOneDir(m_indiOneDirCandleSeries, GetPeriod(), st);
    std::vector<SRGroup> clustMinMax = srClustInt.ConvertCluster(m_period, clust, GetPeriod().GetSpread());
    for (SRGroup a : clustMinMax)
    {
        //log << "Retr level = " << a.min << endl;
    }
*/
    /*
    const Abstracts & abstr = GetAbstracts();
    //const AbstractsStrat & abstrStrat = GetAbstractsStrat();

    int lastPosSeriesThis = m_indiOneDirCandleSeries.GetPosLastSignal(st);
    int lastPosSeriesInv  = m_indiOneDirCandleSeries.GetPosLastSignal(st.Next().Invert());
    ASSERT_POSITIVE_OR_RET_FALSE(lastPosSeriesThis);
    ASSERT_POSITIVE_OR_RET_FALSE(lastPosSeriesInv);

    const Candle & cRange = m_indiOneDirCandleSeries.GetRange(st.Shift(lastPosSeriesThis));
    const Candle & cRangeInv = m_indiOneDirCandleSeries.GetRange(st.Shift(lastPosSeriesInv));
    const float close = abstr.AbstractGetClose(st.i);

    if (not m_cc.IsInCandle(cRange, close))
    {
        return false;
    }
    if (m_cc.IsInCandle(cRangeInv, close))
    {
        if (lastPosSeriesInv < lastPosSeriesThis)
        {
            return false;
        }
    }

    const State st1dStart = m_indiOneDirCandleSeries.GetPosSignalStart(st.Shift(lastPosSeriesThis));
    const State st1dEnd =   m_indiOneDirCandleSeries.GetPosSignalEnd(st.Shift(lastPosSeriesThis));
    const std::vector<SRFinal> & vsr = m_patPinbarSR.GetLevels(st);
    for (const SRFinal & sr : vsr)
    {
        int srStart = sr.GetStart();
        int st1dStarti = st1dStart.i;
        int st1dEndi = st1dEnd.i;
        if (st1dStarti >= srStart && srStart >= st1dEndi - 1)
        {
            // OK
        }
        else
        {
            return false; // At least one broken SR didn't belong to the retracement in question
        }
    }
*/

/*
int RegressionOpti::GetLaterOptiBak(const IPeriod & period, Direction bullish, int later, int degree, float spread, int soonerTemp) const
{
    int ret = 0;
    //const float maxRelMinimum = 1.1; // Good values are between 0.9 and 1.06;
    if (m_verbose)
    cout << endl;
    VecOp vop;
    RegressionRange rra;
    const int barsMin = gcfg.REGRESS_MIN_SAMPLES;
    const int barsMax = soonerTemp > 0 ? abs(later - soonerTemp) : gcfg.REGRESS_MAX_SAMPLES;
    //const int barsMax = abs(later - soonerTemp);
    const int bufMax = 7;
    const int idxMid = (bufMax - 1) / 2;

    Buffer bufAtr = period.GetBuf(BUF_ATR);
    const float atri = bufAtr[later]; // Uwaga tutaj - musi byc ostatni, zeby byl wspolny mianownik
    float prevCoeff = -1;
    EnjoLib::VecD dataGnuplot, argGnuplot;
    EnjoLib::VecF buf;
    //EnjoLib::VecF minima, maxima;
    int lastMinimum = -1;
    //VecF  minima;
    float maxMaximum = -1;
    int maxMaximumIdx = -1;
    float minMinimum = -1;
    int minMinimumIdx = -1;
    for (int sooner = later + barsMin, i = 0; sooner < later + barsMax && sooner < period.Len(); ++sooner, ++i)
    {
        const RegResultXY & regXY = rra.GetXYHigh(period, 0, sooner, later, degree);
        if (regXY.regRes.coeffs.size() == 0)
            return 0;
        const float lastCoef = regXY.regRes.coeffs.back();
        //const float rmsRel = regXY.regRes.rms / atri;
        const float rmsRel = regXY.regRes.merr / atri;
        //const float rmsRel = (bullish ? regXY.pointsOver : regXY.pointsUndr) / atri; /// Czy na pewno dobry kierunek?
        const int regDiff = abs(sooner - later);
        //cout << "Reg diff = " << regDiff;
        //cout << " sooner = " << sooner << ", rms2atr = " << rmsRel << endl;
        if (prevCoeff != -1)
        {
            if (lastCoef * prevCoeff < 0)
            {
                if (m_verbose)
                    cout << "Sign change at " << i << endl;
            }
        }
        const float pointsDistrib = regXY.regPts.GetPoints();
        dataGnuplot.push_back(pointsDistrib);
        //dataGnuplot.push_back(rmsRel);
        argGnuplot.push_back(regDiff);
        buf.push_back(rmsRel);

        if (bullish)
        {
            if (lastCoef < 0)
            {
                continue;
            }
        }
        else
        {
            if (lastCoef > 0)
            {
                continue;
            }
        }
        if (maxMaximum == -1 || rmsRel > maxMaximum)
        {
            maxMaximum = rmsRel;
            maxMaximumIdx = sooner;
        }
        if ((minMinimum == -1 || pointsDistrib < minMinimum) && pointsDistrib > 0)
        {
            minMinimum = pointsDistrib;
            minMinimumIdx = sooner;
            cout << "Minimum at date = " << period.GetCandles()[minMinimumIdx].GetDate() << ", i = " << i << ", val = " << minMinimum << endl;
        }



        if (buf.size() > 5)
        {
            buf.erase(buf.begin(), buf.begin() + 1);
            float val = buf[idxMid];
            int maxIdx = vop.FindMaxIdx(buf);
            int minIdx = vop.FindMinIdx(buf);
            if (maxIdx == idxMid)
            {
                 if (m_verbose)
                cout << "Found MAX at " << i << endl; /// UWAGA, bo bedziemy mieli przesuniecie o polowe szerokosci bufora?
            } else
            if (minIdx == idxMid)
            {
                if (m_verbose)
                    cout << "Found min at " << i;
                //continue;
                //cout << "val = " << val << endl;
                //const float mean = minima.Mean();
                //minima.push_back(val);

                if (mean > 0)
                {
                    const float valRel = val / mean;
                    cout << ", Relavite to mean = " << valRel;
                    if (valRel > maxRelMinimum)
                    {
                        cout << ", Exceeds max by = " << valRel - maxRelMinimum;
                        if (lastMinimum > 0)
                        {
                            continue;

                            ret = lastMinimum;

                            GnuplotPlotTerminal1d(dataGnuplot)
                            return ret;
                        }
                    }

                }

                 if (m_verbose)
                cout << endl;
                lastMinimum = sooner;
            }
        }


        prevCoeff = lastCoef;
    }


    if (m_verbose)
    {
        GnuplotIOSWrap gpl;
        //gpl.Add1d(argGnuplot);

        gpl.Cmd("set terminal dumb 105 24");
        //gpl.Cmd("set yrange [0:*]");
        gpl.Cmd("plot '-' using 1 with lines notitle");
        gpl.Add1d(dataGnuplot);
    }


    if (minMinimumIdx < 0)
        return 0;
    return minMinimumIdx;
}
*/

/*
EnjoLib::Str SvmUtil::CandlesToFeatureVectorStr(const VecCan & det) const
{
    EnjoLib::Osstream oss;
    for (unsigned i = 0; i < det.size(); ++i)
    {
        const Candle & can = det.at(i);
        if (highOnly)
        {
            //oss << (i+1) << ":" << can.GetLow() << " ";
            oss << (i+1) << ":" << CandleCalc().GetMidPrice(can) << " ";
        }
        else
        {
            const int num = 3;
            int j = (i+1) * num;
            oss << (j-2) << ":" << can.GetClose() << " ";
            oss << (j-1) << ":" << can.GetHigh() << " ";
            oss << (j-0) << ":" << can.GetLow() << " ";
        }
    }
    return oss;
}

EnjoLib::VecF SvmUtil::CandlesToFeatureVector(const VecCan & det) const
{
    EnjoLib::VecF ret;
    for (unsigned i = 0; i < det.size(); ++i)
    {
        const Candle & can = det.at(i);
        if (highOnly)
        {
            //ret.push_back(can.GetLow());
            ret.push_back(CandleCalc().GetMidPrice(can));
        }
        else
        {
            ret.push_back(can.GetClose());
            ret.push_back(can.GetHigh());
            ret.push_back(can.GetLow());
        }
    }
    return ret;
}
*/

/*
void TxtSimulator::ClosedOrders(QCustomPlot *customPlot, const IPeriod & period, const Simulator & sim, double time0, double offset, const PlotDataBase & d) const
{
    auto vstdDev = d.GetBuf(BUF_ATR);
    GeneralMath gm;
    const IBufferCandles & bufCandles = period.GetCandles();
    for (const OrderMarket & o : sim.GetOrdersClosed())
    {
        int iOpen = bufCandles.Len() - bufCandles.GetIndex(o.GetOpenDate());
        int iClose = bufCandles.Len() - bufCandles.GetIndex(o.GetCloseDate());

        double fakeOpen = Util::ToNoWeekendSeconds(time0, iOpen, period) - offset;
        double fakeClose = Util::ToNoWeekendSeconds(time0, iClose, period) - offset;

        float open = o.GetOpen();
        float close = o.GetClose();

        QCPItemLine * line = new QCPItemLine(customPlot);
        //line->start->setType(QCPItemPosition::PositionType::ptPlotCoords);
        //line->end->setType(QCPItemPosition::PositionType::ptPlotCoords);
        line->start->setCoords(fakeOpen, open);
        line->end->setCoords(fakeClose, close);
        QPen pen = o.GetDir() == BUY ? QPen("Green") : QPen("Red");
        pen.setWidth(2);
        line->setPen(pen);
        line->setHead(QCPLineEnding(QCPLineEnding::esFlatArrow));
        customPlot->addItem(line);


        QCPItemText * txt = new QCPItemText(customPlot);
        QString strProc = QString::number(gm.round(o.GetProfitProc() * 10000) / 100.) + "%";
        QString strCap = QString::number(gm.round(o.GetCapUsed() * 1000) / 1000.);
        //QString strDate = QString::number(o.GetOpenDate());
        txt->setText(strProc + "\n" + strCap + "\n");
        double stdDev = vstdDev[iOpen];
        double hi = d.GetFinancial()[iOpen].high;
        double y = (hi + stdDev * 4);
        txt->position->setCoords(fakeOpen, y); // place position at center/top of axis rect
        customPlot->addItem(txt);
    }
}
*/

/*

bool StrategyMultiTF::IsSignShift(const State & st) const
{
    Buffer bufTest = m_data.GetBuf(BUF_TEST);
    const float bufTestVal = bufTest[st];
    const float bufTestValPrev = bufTest[st.Next()];
    if (st.bullish)
    {
        if (bufTestValPrev > 0 && bufTestVal < 0)
        {
            return true;
        }
    }
    else
    {
        if (bufTestValPrev < 0 && bufTestVal > 0)
        {
            return true;
        }
    }
    return false;
}

bool StrategyMultiTF::IsRanging(const State & st) const
{
    const float avgSignChange = GetAvgSignChange(st, 5);
    return EnjoLib::GeneralMath().Fabs(avgSignChange) < 5;
}

float StrategyMultiTF::GetAvgSignChange(const State & st, unsigned num) const
{
    Buffer bufTest = m_data.GetBuf(BUF_TEST);
    VecF  obs;
    unsigned numSignChange = 0;
    for (State sti = st; sti.i < m_data.Len()-1 && numSignChange < num; ++sti)
    {
        const float bufValPrev = bufTest[sti.Next()];
        obs.push_back(bufValPrev);
        if (IsSignShift(sti) || IsSignShift(sti.Invert()))
        {
            numSignChange++;
            //obs.push_back(bufValPrev);
        }
    }
    return obs.Mean();
}

Buffer bufTest = m_data.GetBuf(BUF_TEST);
    const float bufTestVal = bufTest[st];
    const float minVal = 20.0 * (st.bullish ? -1 : 1);
    const float maxVal = 60.0 * (st.bullish ? -1 : 1);
    if (Logic::GT(bufTestVal, minVal, st))
    {
        //return false;
    }
    if (Logic::LT(bufTestVal, maxVal, st))
    {
        //return false;
    }

    const float bufTestValPrev = bufTest[st.Next()];
    if (EnjoLib::GeneralMath().Fabs(bufTestValPrev) < 20)
    {
        return false;
    }
    if (IsRanging(st))
    {
        if (not IsSignShift(st)) // Invert na trending, normal na ranging
        {
            return false;
        }
    }
    else
    {
        if (not IsSignShift(st.Invert())) // Invert na trending, normal na ranging
        {
            return false;
        }
    }


    return true;
    */
