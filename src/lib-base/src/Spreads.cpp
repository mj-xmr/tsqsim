#include "Spreads.h"
#include "ConfigGlob.h"
#include "TradeUtil.h"
#include "SpreadsDynamic.h"

#include <Util/PimplDeleter.hpp>
#include <Util/CharManipulations.hpp>
#include <STD/Map.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Str.hpp>
#include <unordered_map>

using namespace std;
using namespace EnjoLib;

struct Spreads::Impl
{
    //SpreadsDynamic m_spreadsDyn; // TODO
    std::unordered_map<std::string, float> m_mapSpreads;
};
PIMPL_DELETER(Spreads)
        
Spreads::~Spreads(){}
Spreads::Spreads()
: m_impl(new Impl())
{
    auto & mapSpr = GetImplRW().m_mapSpreads;
    mapSpr["AUDUSD"] = 0.00018;
    mapSpr["EURAUD"] = 0.00046;
    mapSpr["EURCAD"] = 0.00032;
    mapSpr["EURGBP"] = 0.00017;
    mapSpr["EURUSD"] = 0.00015;
    mapSpr["GBPCHF"] = 0.00035;
    mapSpr["GBPUSD"] = 0.00020;
    mapSpr["NZDUSD"] = 0.00025;
    mapSpr["USDCAD"] = 0.00025;
    mapSpr["USDCHF"] = 0.00025;
    mapSpr["USDJPY"] = 0.016;
    mapSpr["AUDJPY"] = 0.022;
    mapSpr["EURJPY"] = 0.022;
    mapSpr["GBPJPY"] = 0.040;
    mapSpr["NZDJPY"] = 0.03;
    mapSpr["EURCHF"] = 0.00018;
    mapSpr["CHFJPY"] = 0.028;

    mapSpr["XAGUSD"] = 0.02500;
    mapSpr["XAUUSD"] = 0.270;
    mapSpr["XCUUSD"] = 0.022;
    mapSpr["BCOUSD"] = 0.035;
    mapSpr["WTICOUSD"] = 0.027;
    mapSpr["USOIL"] = mapSpr["WTIUSD"] = mapSpr["WTICOUSD"]; // same shit, different name

    mapSpr["AUDCAD"] = 0.00027;
    mapSpr["AUDNZD"] = 0.00044;
    mapSpr["EURCAD"] = 0.00032;
    mapSpr["EURNZD"] = 0.00054;
    mapSpr["GBPAUD"] = 0.00063;
    mapSpr["GBPCAD"] = 0.00063;
    mapSpr["GBPNZD"] = 0.00094;
    mapSpr["NZDCAD"] = 0.00045;

    mapSpr["AUXAUD"] = 2.2;
    mapSpr["ETXEUR"] = 2.0;
    mapSpr["FRXEUR"] = 2.0;
    mapSpr["GRXEUR"] = 2.0;
    mapSpr["UKXGBP"] = 4.0;
    mapSpr["SPXUSD"] = 0.7;

    mapSpr["AU200AUD"] = mapSpr["AUXAUD"]; // same shit, different name
    mapSpr["EU50EUR"] = mapSpr["ETXEUR"]; // same shit, different name
    mapSpr["FR40EUR"] = mapSpr["FRXEUR"]; // same shit, different name
    mapSpr["DE30EUR"] = mapSpr["GRXEUR"]; // same shit, different name
    mapSpr["UK100GBP"] = mapSpr["UKXGBP"]; // same shit, different name
    mapSpr["SPX500USD"] = mapSpr["SPXUSD"]; // same shit, different name

}

static bool first = true;
float Spreads::GetSpread(const EnjoLib::Str & s, double currentPrice) const
{
    if (!gcfg.USE_SPREADS)
        return 0;
    if (s.empty())
    {
        LOGL << "Empty symbol name" << Nl;
        return 0;
    }
    /*
    const double spreadDyn = GetImpl().m_spreadsDyn.GetSpread(s, currentPrice);
    if (spreadDyn != 0)
        return spreadDyn;
    */
    if (not GetImpl().m_mapSpreads.count(s.strRef()))
    {
        CharManipulations cm;
        if (cm.ToLower(s) == "fake")
        {
            return 0;
        }
        if (first)
        {
            LOGL << "Spreads::GetSpreads(): Unknown symbol = " << s << Nl;
            first = false;
        }
        return 0;
    }
    else
    {
        const float spread = GetImpl().m_mapSpreads.find(s.strRef())->second;
        return spread;
    }

}

