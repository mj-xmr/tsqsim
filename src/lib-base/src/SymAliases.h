#ifndef SYMALIASES_H
#define SYMALIASES_H

#include <Util/Str.hpp>
#include <Util/Pimpl.hpp>

class SymAliases
{
    public:
        SymAliases();
        virtual ~SymAliases();

        EnjoLib::Str GetAlias(const EnjoLib::Str & symName) const;

    protected:

    private:
        PIMPL
};

#endif // SYMALIASES_H
