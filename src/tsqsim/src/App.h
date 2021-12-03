#ifndef APP_H
#define APP_H

#include <Util/Str.hpp>

class ConfigSym;

class App
{
    public:
        App();
        virtual ~App(){}

        void Run(const ConfigSym & cfgSymCmdLine) const;

    protected:

    private:
};

#endif // APP_H
