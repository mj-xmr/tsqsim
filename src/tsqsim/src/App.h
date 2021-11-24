#ifndef APP_H
#define APP_H

#include <Util/Str.hpp>

class App
{
    public:
        App();
        virtual ~App(){}

        void Run(const EnjoLib::Str & plugin);

    protected:

    private:
};

#endif // APP_H
