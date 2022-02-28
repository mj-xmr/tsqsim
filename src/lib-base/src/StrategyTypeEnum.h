#ifndef STRATEGYTYPEENUM_H_INCLUDED
#define STRATEGYTYPEENUM_H_INCLUDED

namespace StrategyFactory
{
    enum class Type : int
    {
        STRA_CACHE_FILL,
        STRA_DUMMY,
        STRA_LIVE,
        STRA_TESTING,

        STRA_SEASONAL,
        STRA_WEEKEND,
        STRA_WEEKEND2,
        STRA_REG_FAST,
        STRA_REG_COUNTER,
        STRA_REG_TREND,
        STRA_SR_BRK,
        STRA_SR_BRK_ML,
        STRA_STATION,
        STRA_STATION_BULL,
        STRA_STATION_BEAR,
        STRA_ML_TEST,
        STRA_MA_CROSS_ML,
        STRA_STATION_ML,
        STRA_DTW,
        STRA_DTW_BULL,
        STRA_DTW_BEAR,
        STRA_PAIR,
        STRA_WASH,
        STRA_NOV,
        STRA_RANGE,
        STRA_REG_ZZ,
        STRA_ZZ,
        STRA_NOV_INSTANT_MAXI,
        STRA_NOV_INSTANT_MINI,
        STRA_NOV_INSTANT_MAXI_DIR,
        STRA_REG_STD,
        STRA_REG_STD_LAB,
        STRA_MULTI_TF,
        STRA_MARKET,
        //STRA_DAILY,
        STRA_MACD,
        //STRA_NO_SL,
        STRA_TEFO1,
        //STRA_TEFO1_BUY,
        STRA_TEFO_PROD,
        //STRA_TEFO_PROD_BUY,

        //STRA_SMOOTH,
        STRA_GARCH_NOVEL,
        //STRA_REVERSE,
        //STRA_MA_RUN,
        //STRA_MA_REP,
        //STRA_DIV,
        //STRA_DIV_POT,
        //STRA_MA,
        STRA_MA_CROSS,
        //STRA_RETRACE_DET,
        //STRA_RETRACE_DET2,
        //STRA_RETRACE,
        //STRA_RETRACE_LAB,
        //STRA_REGRESS,
        //STRA_ROUND_BOT,
        //STRA_ROUND_BOT_DET,
        //STRA_ROUND_BOT_LAB,

        //STRA_SIN,///
        //STRA_MA_DIST,
        //STRA_FX_BOOK,
        //STRA_ZZ_STOCH,
        //STRA_ZZ_DUAL,
        STRA_BUY_HOLD,
        //STRA_SVM_QFIN,
        //STRA_SVM,
        //STRA_SVM_PY,
        //STRA_MA_TR,

        //STRA_WEEKEND_RETR,
        STRA_LAST
    };
};


#endif // STRATEGYTYPEENUM_H_INCLUDED
