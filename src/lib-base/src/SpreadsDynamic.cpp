#include "SpreadsDynamic.h"
#include "ConfigDirs.h"

#include <Ios/Ifstream.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Template/AlgoSTDThin.hpp>
#include <Util/PimplDeleter.hpp>

#include <STD/Map.hpp>


using namespace std;
using namespace EnjoLib;

struct SpreadsDynamic::Impl
{
    std::map<EnjoLib::Str, double> m_mapSpreadsRelativeToPrice;
};
PIMPL_DELETER(SpreadsDynamic)

SpreadsDynamic::SpreadsDynamic()
: m_impl(new Impl())
{
    try
    {
        Ifstream fileCryptoSpreads(ConfigDirs().FILE_CRYPTO_SPREADS);
        Tokenizer tok;
        for (const Str & line : tok.GetLines(fileCryptoSpreads))
        {
            const VecStr & tokens = tok.Tokenize(line, ',');
            const Str & symbol = tokens.at(0);
            const Str & askbid1 = tokens.at(1);
            const Str & askbid2 = tokens.at(2);
            CharManipulations cms;
            const double askBid1d = cms.ToDouble(askbid1);
            const double askBid2d = cms.ToDouble(askbid2);
            const double hi = AlgoSTDThin().Max(askBid1d, askBid2d);
            const double lo = AlgoSTDThin().Min(askBid1d, askBid2d);

            const double spread =  hi - lo;
            const double priceThen = (hi + lo) / 2.0;
            const double spreadRelativeToPrice = spread / priceThen;

            GetImplRW().m_mapSpreadsRelativeToPrice[symbol] = spreadRelativeToPrice;
        }
    }
    catch (std::exception & ex)
    {
        //cout << "SpreadsDynamic::SpreadsDynamic(): " << ex.what() << endl;
    }
}

double SpreadsDynamic::GetSpread(const EnjoLib::Str & symbolName, double currentPrice) const
{
    const auto it = GetImpl().m_mapSpreadsRelativeToPrice.find(symbolName);
    if (it == GetImpl().m_mapSpreadsRelativeToPrice.end())
        return 0;

    const double spreadRelative = it->second;
    const double spreadFinal = spreadRelative * currentPrice;

    return spreadFinal;
}
