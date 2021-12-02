#include "EnumStringMapBufferType.h"
#include <BufferType.h>

EnumStringMapBufferType::EnumStringMapBufferType()
{
    for (int i = 0; i <= int(BufferTypeEnum::BUF_NONE); ++i)
    {
        BufferTypeEnum type = BufferTypeEnum(i);
        switch (type) // Generate compiler warnings
        {
            case BufferTypeEnum::BUF_NONE:                  Add(type, "None"); break;
            case BufferTypeEnum::BUF_TEST:                  Add(type, "Test"); break;
            case BufferTypeEnum::BUF_STRAT:                 Add(type, "Strat"); break;
            case BufferTypeEnum::BUF_TIME_DIFF:             Add(type, "T Diff"); break;
            
            case BufferTypeEnum::BUF_SSA_OSCI:              Add(type, "Ssa osc"); break;
            case BufferTypeEnum::BUF_SPREADS:               Add(type, "Spreads"); break;
            case BufferTypeEnum::BUF_STATION:               Add(type, "Station"); break;
            case BufferTypeEnum::BUF_REG_VOTE:              Add(type, "RegVote"); break;
            case BufferTypeEnum::BUF_MA_SUPER_FAST:         Add(type, "MA SFast"); break;
            case BufferTypeEnum::BUF_MA_FAST:               Add(type, "MA Fast"); break;
            case BufferTypeEnum::BUF_MA_SLOW:               Add(type, "MA Slow"); break;
            case BufferTypeEnum::BUF_STD_DEV:               Add(type, "StdDev"); break;
            case BufferTypeEnum::BUF_STD_RELATIVE:          Add(type, "StdDev rel"); break;
            case BufferTypeEnum::BUF_SPREAD_PROFIT:         Add(type, "SprePro"); break;
            case BufferTypeEnum::BUF_TRENDNESS:             Add(type, "Trend"); break;
            //case BufferTypeEnum::BUF_TRENDNESS_SMOOTH:      Add(type, "TrendS"); break;
            case BufferTypeEnum::BUF_ADX:                   Add(type, "ADX"); break;
            case BufferTypeEnum::BUF_ATR:                   Add(type, "ATR"); break;
            case BufferTypeEnum::BUF_ATR_RELATIVE:          Add(type, "ATR rel"); break;
            case BufferTypeEnum::BUF_RSI:                   Add(type, "RSI"); break;
            case BufferTypeEnum::BUF_ROC:                   Add(type, "ROC"); break;
            case BufferTypeEnum::BUF_STOCH_K:               Add(type, "Stoch K"); break;
            case BufferTypeEnum::BUF_STOCH_D:               Add(type, "Stoch D"); break;
            //case BufferTypeEnum::BUF_STOCH_FIT:             Add(type, "Stoch Fit"); break;
            //case BufferTypeEnum::BUF_TREND_REGRESS:         Add(type, "Trend Reg"); break;
            //case BufferTypeEnum::BUF_TREND_REGRESS_SMOOTH:  Add(type, "Trend RegS"); break;
            case BufferTypeEnum::BUF_UNIV_OSCI:             Add(type, "Univ osci"); break;
            case BufferTypeEnum::BUF_SIN:                   Add(type, "Sin"); break;
            case BufferTypeEnum::BUF_SIN_LEAD:              Add(type, "Sin Lead"); break;
            case BufferTypeEnum::BUF_SIN_DIFF:              Add(type, "Sin Diff"); break;
            //case BufferTypeEnum::BUF_EDECOMP_UP:            Add(type, "EDe Up"); break;
            //case BufferTypeEnum::BUF_EDECOMP_LO:            Add(type, "EDe Lo"); break;
            //case BufferTypeEnum::BUF_EDECOMP_MID:           Add(type, "EDe Mid"); break;
            case BufferTypeEnum::BUF_MACD:                  Add(type, "macd"); break;
            case BufferTypeEnum::BUF_MACD_SIGNAL:           Add(type, "macd sig"); break;
            case BufferTypeEnum::BUF_MACD_HIST:             Add(type, "macd hist"); break;
            case BufferTypeEnum::BUF_MA_HIST:              Add(type, "mas hist"); break;
            case BufferTypeEnum::BUF_MA_HIST_STD_UP:          Add(type, "mas hi std u"); break;
            case BufferTypeEnum::BUF_MA_HIST_STD_DOWN:        Add(type, "mas hi std d"); break;
            case BufferTypeEnum::BUF_MA_AVG:                Add(type, "mas avg"); break;
            
            case BufferTypeEnum::BUF_TREND_ZZ_MA_CROSS:     Add(type, "Tr zz ma"); break;
            case BufferTypeEnum::BUF_MARKET_REGIME:         Add(type, "Regim"); break;
            case BufferTypeEnum::BUF_TREND_MA:              Add(type, "Tr MA"); break;
            case BufferTypeEnum::BUF_TREND_MA_UP1:          Add(type, "Tr MA1"); break;
            case BufferTypeEnum::BUF_TREND_MA_UP2:          Add(type, "Tr MA2"); break;
            case BufferTypeEnum::BUF_TREND_MA_UP3:          Add(type, "Tr MA3"); break;
            case BufferTypeEnum::BUF_LONG_WICK_BULL:        Add(type, "LWickB"); break;
            case BufferTypeEnum::BUF_LONG_WICK_BEAR:        Add(type, "LWickS"); break;
            case BufferTypeEnum::BUF_LONG_WICK_BULL_REL:    Add(type, "LWickBR"); break;
            case BufferTypeEnum::BUF_LONG_WICK_BEAR_REL:    Add(type, "LWickSR"); break;
            case BufferTypeEnum::BUF_LONG_WICK_SEPARATE:    Add(type, "LWiSep"); break;

            case BufferTypeEnum::BUF_ZZ_STAT:               Add(type, "ZZ Stat"); break;
            case BufferTypeEnum::BUF_SR_BULL:               Add(type, "SR Bull"); break;
            case BufferTypeEnum::BUF_SR_BEAR:               Add(type, "SR Bear"); break;
            case BufferTypeEnum::BUF_ZZ_PROB:               Add(type, "ZZ Prob"); break;
            case BufferTypeEnum::BUF_WKND_PROB:             Add(type, "Wknd Prob"); break;
            case BufferTypeEnum::BUF_NIGHT_PROB:            Add(type, "Night Prob"); break;

            case BufferTypeEnum::BUF_MA_RUN_BULL:           Add(type, "MaRunB"); break;
            case BufferTypeEnum::BUF_MA_RUN_BEAR:           Add(type, "MaRunS"); break;
            case BufferTypeEnum::BUF_INTEREST_1:            Add(type, "Inter 1"); break;
            case BufferTypeEnum::BUF_INTEREST_2:            Add(type, "Inter 2"); break;
            case BufferTypeEnum::BUF_INTEREST_DIFF:         Add(type, "Inter Dif"); break;
            case BufferTypeEnum::BUF_BBAND_UP:              Add(type, "BB Up"); break;
            case BufferTypeEnum::BUF_BBAND_DOWN:            Add(type, "BB Down"); break;

            /*
            case BufferTypeEnum::BUF_HMM_STATES:
                Add(type, "Hmm Sts"); break;
            case BufferTypeEnum::BUF_HMM_PROB1:
                Add(type, "Hmm Prb1"); break;
            case BufferTypeEnum::BUF_HMM_PROB2:
                Add(type, "Hmm Prb2"); break;
            case BufferTypeEnum::BUF_HMM_PROB3:
                Add(type, "Hmm Prb3"); break;
            */
        }
    }
}

EnumStringMapBufferType::~EnumStringMapBufferType(){}
