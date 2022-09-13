#include "SymAliases.h"
#include "TradeUtil.h"

#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/PimplDeleter.hpp>

#include <STD/Map.hpp>

using namespace std;
using namespace EnjoLib;

struct SymAliases::Impl
{
    std::map<EnjoLib::Str, EnjoLib::Str> m_map;
};
PIMPL_DELETER(SymAliases)

SymAliases::SymAliases()
: m_impl(new Impl())
{
    GetImplRW().m_map["USOIL"] = GetImplRW().m_map["WTICOUSD"] = "WTIUSD";
}

SymAliases::~SymAliases(){}

static bool first = true;
EnjoLib::Str SymAliases::GetAlias(const EnjoLib::Str & symName) const
{
    EnjoLib::Str s = symName;
    if (s.empty())
    {
        LOGL << "Empty symbol name" << Nl;
        return "";
    }
    CharManipulations cm;
    //s = TradeUtil().CutSymbolTestingPrefix(s);
    if (not GetImpl().m_map.count(s))
    {
        if (first)
        {
            //cout << "SymAliases::GetAlias(): Unknown symbol = " << s << endl;
            first = false;
        }
        return symName;
    }
    else
    {
        const EnjoLib::Str alias = GetImpl().m_map.find(s)->second;
        return alias;
    }
}
