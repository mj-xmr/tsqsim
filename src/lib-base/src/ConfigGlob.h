#ifndef CONFIG_H
#define CONFIG_H

#include "Direction.h"
#include <Template/ArrayFwd.hpp>

#include <3rdParty/stdfwd.hh>

class StrategyType;

class ConfigGlob
{
public:
    ConfigGlob();
    virtual ~ConfigGlob(){}

    bool PENDING_ADD = true;
    bool PENDING_ERASE_PREVIOUS = false;
    bool PENDING_PROFITS = true;
    bool SR_USE = true;
    float START_CAP = 3;
    float MIN_SCORE;
    float MAX_LOSS_PERCENT;
    float LEVERAGE_MUL = 1;
    float CORREL_MIN = 0.7;
    float SHARPE_MIN = 0.1;
    float MAX_DD_MAX = 0.1;
    float MAX_DD_MAX_TOTAL = 0.1;
    float MAX_CAP_USAGE = 0.75;
    int BROKER_LEVERAGE = 20;
    int MAX_MA_PERIOD_DIST;
    int MAX_MA_REP_PULLBACKS;
    int NUM_TPS; // Take profits
    int PERIOD_TECH_STANDARD = 14;
    int PERIOD_TECH_30 = 30;
    int PERIOD_TECH_TREND_SMOOTH = 4;
    int PERIOD_TECH_STD_DEV_REL = 45;
    int HORIZON_YEAR_START = 2010;
    int HORIZON_YEAR_END = 0;
    int HORIZON_MONTH_START = 1;
    int HORIZON_MONTH_END = 0;
    float SVM_MIN_GAIN;
    int     REGRESS_MIN_SAMPLES = 70;
    int     REGRESS_MAX_SAMPLES = 350;
    float   REGRESS_SIZE_BONUS = 3.0;

    int PORT_PY_SERV = 8071;

    bool USE_SPREADS = true;
    bool CAP_SECURE = true;
    bool CAP_SMOOTH = true;
    bool PARTIAL_TP = true;
    bool SYMBOLS_MULTITHREAD = true;
    bool WARNINGS = false;

    bool PLOT_QT = false;
    bool IS_QT = false;
    bool PLOT_GNUPLOT = true;
    bool SIMUL_ACCU_SCREENSHOTS = true;
    bool SIMUL_SCREENSHOTS = true;
    bool SIMUL_VERBOSE = false;

    bool OPTI_USE = true; /// TODO: Ditch? YES! ASAP!

    bool SIGNALS_MINATURES = true;
    bool SIGNALS_PYTHON = false;
    bool SIGNALS_MULTI_FRAME = false;
    bool SIGNALS_CREATE = false;
    bool TRAIN_CREATE = false;
    bool LABELS_CREATE = false;

    bool REPORT_SORT = false;
    bool REPORT_HIDE_IGNORED = true;

    bool USE_CACHE = true;
    Direction DIRECTION = SELL;

    EnjoLib::Array<StrategyType> GetStrategies() const;
    EnjoLib::Array<StrategyType> GetStrategiesTested() const;

protected:
private:
};

extern ConfigGlob gcfg;

#endif // CONFIG_H
