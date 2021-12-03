#ifndef CLI_H
#define CLI_H

#include <Util/Str.hpp>
#include <Util/Result.hpp>

struct CLIResult;

class CLI
{
    public:
        CLI();
        virtual ~CLI();
        
        EnjoLib::Result<CLIResult> GetConfigs(int argc, char ** argv) const;
        
        virtual EnjoLib::Str GetAdditionalHelp() const = 0;

    protected:

    private:
};

#endif // CLI_H
