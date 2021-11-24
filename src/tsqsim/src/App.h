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
        void UpdateCfgSym(const ConfigSym & cfgSymCmdLine, ConfigSym & cfgFile) const;

    private:
};

#endif // APP_H
