#ifndef SYMBOLALTERNATIVES_H
#define SYMBOLALTERNATIVES_H

#include <Util/Str.hpp>
#include <Util/BimapBase.hpp>

class SymbolAlternatives
{
    public:
        SymbolAlternatives();
        virtual ~SymbolAlternatives();

        EnjoLib::Str Get(const EnjoLib::Str & sym) const;

    protected:

    private:
        EnjoLib::SafePtr<EnjoLib::BimapBase<EnjoLib::Str, EnjoLib::Str>> m_altsPtr;
        EnjoLib::BimapBase<EnjoLib::Str, EnjoLib::Str> & m_alts;
};

#endif // SYMBOLALTERNATIVES_H
