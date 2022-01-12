#ifndef APP_H
#define APP_H

#include <Util/Str.hpp>

class ConfigSym;
class ISymbol;
class IPeriod;

class App
{
    public:
        App();
        virtual ~App(){}

        void Run(const ConfigSym & cfgSymCmdLine) const;
        void Optim(const ISymbol & sym, const IPeriod & per) const;
        void XValid(const ISymbol & sym, const IPeriod & per) const;

    protected:

    private:
};

#endif // APP_H
