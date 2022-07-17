#include "ConfigGlob.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include "TradeUtil.h"
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

//#include <set>

using namespace std;

EnjoLib::Array<StrategyType> ConfigGlob::GetStrategies() const
{
    vector<StrategyType> strat {
         //StrategyFactory::Type::STRA_WEEKEND2
        //,
        //StrategyFactory::Type::STRA_SR_BRK
        //StrategyFactory::Type::STRA_REG_COUNTER
        //StrategyFactory::Type::STRA_DTW
        //,StrategyFactory::Type::STRA_MA_CROSS_ML
        //,StrategyFactory::Type::STRA_ML_TEST


         StrategyFactory::Type::STRA_STATION_BULL
        ,StrategyFactory::Type::STRA_STATION_BEAR

        //,StrategyFactory::Type::STRA_WEEKEND2
        //,StrategyFactory::Type::STRA_NOV_INSTANT_MAXI
        //,StrategyFactory::Type::STRA_REG_ZZ
        //,StrategyFactory::Type::STRA_ZZ
        //,StrategyFactory::Type::STRA_DAILY
        //,StrategyFactory::Type::STRA_MULTI_TF
        //,StrategyFactory::Type::STRA_NOV_INSTANT_MAXI_DIR
        //,StrategyFactory::Type::STRA_PAIR
        //,StrategyFactory::Type::STRA_REG_STD
        //,StrategyFactory::Type::STRA_WASH
        //,StrategyFactory::Type::STRA_ROUND_BOT_DET
        //,StrategyFactory::Type::STRA_NOV
        };
    return strat;
}

EnjoLib::Array<StrategyType> ConfigGlob::GetStrategiesTested() const
{
    vector<StrategyType> strat {
         //StrategyFactory::Type::STRA_WEEKEND2
        //,
        //StrategyFactory::Type::STRA_SR_BRK // Already tested in "system". Would bite each other.
        StrategyFactory::Type::STRA_REG_COUNTER, /// TODO: fails for static & O3=OFF
        //StrategyFactory::Type::STRA_DTW
        //,StrategyFactory::Type::STRA_MA_CROSS_ML
        //,StrategyFactory::Type::STRA_ML_TEST
        StrategyFactory::Type::STRA_STATION_BULL
    };
    return strat;
}

ConfigGlob::ConfigGlob()
{
    MAX_LOSS_LIVE_PERCENT = 1.4;
    //PLOT_GNUPLOT = false;
    MIN_SCORE = 0.01;
    MAX_LOSS_PERCENT = 2;
    //START_CAP = 1.73;
    START_CAP = 5;
    CORREL_MIN = 0.95; // crypto = 90
    SHARPE_MIN = 0.10; // crypto = 15
    MAX_DD_MAX = 0.05; // crypto = 0.05
    MAX_DD_MAX_TOTAL = 0.15;
    MAX_CAP_USAGE = 0.75;
// SPREAD = 0.00018 / 2.0;
    MAX_MA_PERIOD_DIST = 30;
    MAX_MA_REP_PULLBACKS = 4;
    NUM_TPS = 10;

    SVM_MIN_GAIN = 0.5 / 100.0;
    REGRESS_MIN_SAMPLES = 10;
    REGRESS_MAX_SAMPLES = 120;
    REGRESS_SIZE_BONUS = 1.0;

    //LEVERAGE_MUL = 16;
    //LEVERAGE_MUL = 8;
    LEVERAGE_MUL = 5;


    //TradeUtil().GetYearMonthMax()
    HORIZON_YEAR_END = 2018; HORIZON_MONTH_END = 12;
    //HORIZON_YEAR_START = 2007; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2010; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2014; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2014; HORIZON_MONTH_START = 8; // shift to conform to H4 MT simulator
    HORIZON_YEAR_START = 2013; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2016; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2014; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2015; HORIZON_MONTH_START = 4;
    //HORIZON_YEAR_START = 2015; HORIZON_MONTH_START = 11;
    //HORIZON_YEAR_START = 2003; HORIZON_MONTH_START = 7;

    //HORIZON_YEAR_START = 2016; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2016; HORIZON_MONTH_START = 12;
    //HORIZON_YEAR_START = 2017; HORIZON_MONTH_START = 1;
    //HORIZON_YEAR_START = 2017; HORIZON_MONTH_START = 9;
    //HORIZON_YEAR_END =   2016; HORIZON_MONTH_END =   2;
    //HORIZON_YEAR_END =   2012; HORIZON_MONTH_END =   7;
    //HORIZON_YEAR_END =   2014; HORIZON_MONTH_END =   12;
    //HORIZON_YEAR_END =   2015; HORIZON_MONTH_END =   10;
    //HORIZON_YEAR_END =   2016; HORIZON_MONTH_END =   6;
    //HORIZON_YEAR_END =   2017; HORIZON_MONTH_END =   5;

    ///HORIZON_YEAR_START = 2015; HORIZON_MONTH_START = 3; // BUG na MAX 2017.06 i GBPJPY confSym.yearStart -= 3; // test

    //SYMBOLS_MULTITHREAD = false;

    REPORT_SORT = false; // Sort by points gained?
    REPORT_HIDE_IGNORED = true; // Hide signals with ignored points? (less points than minimum). Makes sense with REPORT_SORT=false for debugging.

    //REPORT_FULL = false; // All currencies?
    SIMUL_ACCU_SCREENSHOTS = false; // Generate screenshots for accumulated report?
    SIMUL_SCREENSHOTS = false; // Generate individual currency results?

    //SIMUL_VERBOSE = true; // Show individual trades output?
    //SIMUL_MULTITHREAD = false;
    //WARNINGS = true;

    //SR_USE = false;

    //LABELS_CREATE = true;
    //SIGNALS_CREATE = true; // Show price shots
    SIGNALS_MULTI_FRAME = false;
    SIGNALS_MINATURES = !SIGNALS_MULTI_FRAME;
    //SIGNALS_MINATURES = false;
    //SIGNALS_PYTHON = true;
    //DIRECTION = BUY;
    //USE_SPREADS = false;
    //REPEAT = true;
    //USE_CACHE = false;
    PARTIAL_TP = false;
    PENDING_ADD = false;
    PENDING_ERASE_PREVIOUS = true;
    //PENDING_PROFITS = false;
    //POS_ADD = false;
    //OPTI_USE = false;

//    STRATEGIES = vector<const StrategyType &>{const StrategyType &::MA, const StrategyType &::MA_REP};
/*

*/
    //CAP_SECURE = false;
    //CAP_SMOOTH = false;

    MAX_MA_REP_PULLBACKS = 12;
    NUM_TPS = 10;
}

ConfigGlob gcfg;
