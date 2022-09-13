#ifndef CLITSQ_H
#define CLITSQ_H

#include "CLI.h"

#include <Util/StrFwd.hpp>
#include <Util/Result.hpp>

struct CLIResult;

class CLITsq : public CLI
{
    public:
        CLITsq();
        virtual ~CLITsq();

        EnjoLib::Str GetAdditionalHelp() const override;

    protected:

    private:
};

#endif // CLITSQ_H
