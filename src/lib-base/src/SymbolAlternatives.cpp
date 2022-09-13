#include "SymbolAlternatives.h"
#include <Util/Str.hpp>
#include <Util/Bimap.hpp>

SymbolAlternatives::~SymbolAlternatives(){}
SymbolAlternatives::SymbolAlternatives()
: m_altsPtr(new EnjoLib::Bimap<EnjoLib::Str, EnjoLib::Str>)
, m_alts(*m_altsPtr)
{
    m_alts.Add("WTICOUSD", "WTIUSD");

    m_alts.Add("AU200AUD",  "AUXAUD");
    m_alts.Add("EU50EUR",   "ETXEUR");
    m_alts.Add("FR40EUR",   "FRXEUR");
    m_alts.Add("DE30EUR",   "GRXEUR");
    m_alts.Add("UK100GBP",  "UKXGBP");
    m_alts.Add("SPX500USD", "SPXUSD");
}

EnjoLib::Str SymbolAlternatives::Get(const EnjoLib::Str & sym) const
{
    if (m_alts.Has1(sym))
        return m_alts.Get1(sym);
    if (m_alts.Has2(sym))
        return m_alts.Get2(sym);

    return sym;
}
