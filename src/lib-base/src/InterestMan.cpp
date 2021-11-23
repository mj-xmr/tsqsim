#include <STD/MapPch.hpp>

#include "InterestMan.h"
#include "ConfigDirs.h"
#include "TradeUtil.h"

#include <Ios/Ifstream.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Except.hpp>
#include <Template/CacheRAMBare.hpp>

#include <STD/VectorCpp.hpp>
#include <Util/CoutBuf.hpp>
#include <STD/Algorithm.hpp>

using namespace EnjoLib;
using namespace std;

InterestMan::InterestMan()
: m_interest(new CacheRAMBare<EnjoLib::Str, std::vector<Interest>>)
{
    //cout << "Interest man = " << ConfigDirs().FILE_INTEREST << endl;
    try
    {
    Ifstream inInterest(ConfigDirs().FILE_INTEREST);
    const Tokenizer tok;
    for (const Str & line : tok.GetLines(inInterest, true))
    {
        const VecStr & tokens = tok.Tokenize(line, ',');
        const Str sym     = tokens.at(0);
        const Str bidStr  = tokens.at(1);
        const Str askStr  = tokens.at(2);
        const Str dateStr = tokens.at(3);
        //cout << sym << ", " << bid << ", " << ask << ", " << dateStr << endl;
        const CharManipulations cmp;
        const float bid = cmp.ToDouble(bidStr);
        const float ask = cmp.ToDouble(askStr);
        const DateInt date = TradeUtil().DateISOdot2DateInt(dateStr);
        if (not m_interest->Has(sym))
        {
            m_interest->Add(sym, std::vector<Interest>());
        }
        const Interest interest(bid, ask, date);
        m_interest->GetRW(sym).push_back(interest);
        //cout << interest.GetAsk() << endl;
    }
    for (auto it = m_interest->GetMapRW().begin(); it != m_interest->GetMapRW().end(); ++it)
    {
        auto & v = it->second;
        std::reverse(v.begin(), v.end());
    }
	}
	catch(std::exception & ex)
	{
		LOGL << "InterestMan(): " << ex.what() << EnjoLib::Nl;
	}
}

struct InterCmp
{
    bool operator()(const Interest & int1, const DateInt & date2) const
    {
        return int1.GetDate() < date2;
    }

    bool operator()(const DateInt & date2, const Interest & int1) const
    {
        return date2 < int1.GetDate();
    }
};

bool InterestMan::HasSymbol(const EnjoLib::Str & symbol) const
{
    return m_interest->Has(symbol);
}

float InterestMan::GetBid(const EnjoLib::Str & symbol, DateInt date) const
{
    const Interest & inter = GetInterest(symbol, date);
    return inter.GetBid();
}

float InterestMan::GetAsk(const EnjoLib::Str & symbol, DateInt date) const
{
    const Interest & inter = GetInterest(symbol, date);
    return inter.GetAsk();
}

float InterestMan::GetMid(const EnjoLib::Str & symbol, DateInt date) const
{
    const Interest & inter = GetInterest(symbol, date);
    return inter.GetMid();
}

const Interest & InterestMan::GetInterest(const EnjoLib::Str & symbol, DateInt date) const
{
    if (not HasSymbol(symbol))
    {
        throw EnjoLib::ExceptInvalidArg("InterestMan::GetInterest(): Not found symbol " + symbol + ". Use HasSymbol() first!");
    }
    auto vecInterestIt = m_interest->GetMap().find(symbol);
    auto vecIt = vecInterestIt->second;
    bool foundExact = binary_search(vecIt.begin(), vecIt.end(), date, InterCmp());

    auto itFound = lower_bound(vecIt.begin(), vecIt.end(), date, InterCmp());
    if (foundExact)
        return *itFound;
    else
        return *(itFound - 1); // jump to the previous valid
}
