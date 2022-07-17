#include "StrategyFactoryName.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include <Util/Except.hpp>
#include <Ios/Osstream.hpp>

EnjoLib::Str StrategyFactoryName::Create(const StrategyType & type) const
{
    EnjoLib::Str name;
    switch (type.GetType())
    {
        case StrategyFactory::Type::STRA_ML_TEST:               name = "ML test";     break;
        case StrategyFactory::Type::STRA_MA_CROSS_ML:           name = "MaCrossML";   break;
        case StrategyFactory::Type::STRA_STATION_ML:            name = "StationML";   break;
        case StrategyFactory::Type::STRA_DTW:                   name = "Dyn";         break;
        case StrategyFactory::Type::STRA_DTW_BULL:              name = "DynB";        break;
        case StrategyFactory::Type::STRA_DTW_BEAR:              name = "DynS";        break;
        case StrategyFactory::Type::STRA_MARKET:                name = "Market";      break;

        case StrategyFactory::Type::STRA_SEASONAL:              name = "Season";     break;
        case StrategyFactory::Type::STRA_GARCH_NOVEL:           name = "Garch";     break;
        case StrategyFactory::Type::STRA_STATION:               name = "Stat";        break;
        case StrategyFactory::Type::STRA_STATION_BULL:          name = "StatB";       break;
        case StrategyFactory::Type::STRA_STATION_BEAR:          name = "StatS";       break;

        case StrategyFactory::Type::STRA_ZZ:                    name = "ZZ";        break;
        case StrategyFactory::Type::STRA_REG_ZZ:                name = "RegZZ";        break;
        case StrategyFactory::Type::STRA_REG_TREND:             name = "RegTrend";  break;
        case StrategyFactory::Type::STRA_REG_COUNTER:           name = "RegCounter"; break;
        case StrategyFactory::Type::STRA_REG_FAST:              name = "RegFast"; break;

        case StrategyFactory::Type::STRA_NOV_INSTANT_MAXI:      name = "NovInstMax"; break;
        case StrategyFactory::Type::STRA_NOV_INSTANT_MINI:      name = "NovInstMin"; break;
        case StrategyFactory::Type::STRA_NOV_INSTANT_MAXI_DIR:  name = "NovInstMaxDir"; break;
        case StrategyFactory::Type::STRA_RANGE:         name = "Range"; break;
        //case StrategyFactory::Type::STRA_DIV:           name = "Div";       break;
        //case StrategyFactory::Type::STRA_DIV_POT:       name = "DivPot";    break;
        //case StrategyFactory::Type::STRA_MA:            name = "Ma";        break;
        case StrategyFactory::Type::STRA_TEFO1:         name = "TeFo1";       break;
        //case StrategyFactory::Type::STRA_TEFO1_BUY:     name = "TeFo1Buy";    break;
        case StrategyFactory::Type::STRA_TEFO_PROD:     name = "TeFoProd";    break;
        //case StrategyFactory::Type::STRA_TEFO_PROD_BUY: name = "TeFoProdBuy"; break;
        //case StrategyFactory::Type::STRA_NO_SL:         name = "NoSL";        break;
        //case StrategyFactory::Type::STRA_MA_REP:        name = "MaRep";       break;
        //case StrategyFactory::Type::STRA_MA_RUN:        name = "MaRun";       break;
        case StrategyFactory::Type::STRA_SR_BRK:        name = "SRBrk";       break;
        case StrategyFactory::Type::STRA_SR_BRK_ML:      name = "SRBrkML";    break;
        case StrategyFactory::Type::STRA_WASH:          name = "Wash";        break;
        case StrategyFactory::Type::STRA_NOV:           name = "Nov";         break;
        case StrategyFactory::Type::STRA_MA_CROSS:      name = "MaCross";     break;
        //case StrategyFactory::Type::STRA_RETRACE_DET:   name = "RetrDet1";  break;
        //case StrategyFactory::Type::STRA_RETRACE_DET2:  name = "RetraceDet2"; break;
        //case StrategyFactory::Type::STRA_REVERSE:       name = "Reverse";     break;
        //case StrategyFactory::Type::STRA_RETRACE:       name = "Retrace";     break;
        //case StrategyFactory::Type::STRA_RETRACE_LAB:   name = "RetraceLab";  break;
        //case StrategyFactory::Type::STRA_REGRESS:       name = "Regress";     break;
        //case StrategyFactory::Type::STRA_ROUND_BOT:     name = "RoundBot";    break;
        //case StrategyFactory::Type::STRA_ROUND_BOT_DET: name = "RoundBotDet"; break;
        //case StrategyFactory::Type::STRA_ROUND_BOT_LAB: name = "RoundBotLab"; break;
        case StrategyFactory::Type::STRA_PAIR:          name = "Pair";        break;
        case StrategyFactory::Type::STRA_REG_STD:       name = "RegStd";      break;
        case StrategyFactory::Type::STRA_REG_STD_LAB:   name = "RegStdLab";   break;
        case StrategyFactory::Type::STRA_MULTI_TF:      name = "MultiTF";     break;
        //case StrategyFactory::Type::STRA_DAILY:         name = "Daily";       break;
        //case StrategyFactory::Type::STRA_SIN:           name = "Sin";       break;
        //case StrategyFactory::Type::STRA_MA_DIST:       name = "MaDist";    break;
        //case StrategyFactory::Type::STRA_FX_BOOK:       name = "FxBook";    break;
        //case StrategyFactory::Type::STRA_ZZ_STOCH:      name = "ZZStoch";   break;
        //case StrategyFactory::Type::STRA_ZZ_DUAL:       name = "ZZDual";    break;
        case StrategyFactory::Type::STRA_BUY_HOLD:      name = "BH";          break;
        //case StrategyFactory::Type::STRA_SVM_QFIN:      name = "QFin";      break;
        //case StrategyFactory::Type::STRA_SVM:           name = "SVM";       break;
        //case StrategyFactory::Type::STRA_SVM_PY:        name = "SVMpy";     break;
        //case StrategyFactory::Type::STRA_MA_TR:         name = "MaTr";      break;
        case StrategyFactory::Type::STRA_WEEKEND:       name = "WkndNov";     break;
        case StrategyFactory::Type::STRA_WEEKEND2:       name = "Wknd";       break;
        //case StrategyFactory::Type::STRA_WEEKEND_RETR:  name = "WkndRetr"; break;
        case StrategyFactory::Type::STRA_MACD:          name = "MACD";        break;
        //case StrategyFactory::Type::STRA_SMOOTH:        name = "Smooth";      break;
        case StrategyFactory::Type::STRA_CACHE_FILL:    name = "Cache";       break;
        case StrategyFactory::Type::STRA_DUMMY:         name = "Dummy";       break;
        case StrategyFactory::Type::STRA_TESTING:       name = "Testing";     break;
        case StrategyFactory::Type::STRA_LIVE:          name = "Live";     break;
        case StrategyFactory::Type::STRA_LAST:          name = "Last";     break;
    }
    if (name.empty())
    {
        EnjoLib::Osstream oss;
        oss << "StrategyFactoryName::Create(): not defined the name for type " << int(type.GetType()) << EnjoLib::Nl;
        throw EnjoLib::ExceptInvalidArg(oss.str());
    }

    return name;
}

StrategyType StrategyFactoryName::NameToType(const EnjoLib::Str & name) const
{
    for (int i = 0; i <= int(StrategyFactory::Type::STRA_LAST); ++i)
    {
        StrategyType typeFound(i);
        EnjoLib::Str nameFound = Create(typeFound);
        if (nameFound == name)
            return typeFound;
    }
    throw EnjoLib::ExceptInvalidArg("StrategyFactoryName::NameToType(): not found strategy for name '" + name + "'");
}
