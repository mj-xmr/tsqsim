#include "pch_base.h"

#include "Leverages.h"
#include <Util/Str.hpp>
#include <Template/CacheRAMBare.hpp>

using namespace std;

Leverages::Leverages()
: m_mapLeverages(new EnjoLib::CacheRAMBare<EnjoLib::Str, float>)
{
    //const int commodLvg = 20; // Old
    const int commodLvg = 100;
    m_mapLeverages->Add("XAUUSD", commodLvg);
    m_mapLeverages->Add("XCUUSD", commodLvg);
    m_mapLeverages->Add("BCOUSD", commodLvg);
    m_mapLeverages->Add("WTICOUSD", commodLvg);
    m_mapLeverages->Add("WTIUSD", commodLvg);
}

Leverages::~Leverages()
{
    //dtor
}

float Leverages::GetLeverage(const EnjoLib::Str & symbolName) const
{
    return 100;
    /*
    const int accountLvg = 100;
    if (symbolName.empty())
    {
        cout << "Empty symbol name" << endl;
        return accountLvg;
    }
    if (not m_mapLeverages.count(symbolName))
    {
        return accountLvg;
    }
    else
    {
        const float lvg = m_mapLeverages.find(symbolName)->second;
        return lvg;
    }
    */
}
