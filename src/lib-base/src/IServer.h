#ifndef ISERVER1_H
#define ISERVER1_H

#include <Template/CorradePointerFwd.h>

class IServerReceiver;
class IServer
{
    public:
        IServer();
        virtual ~IServer();

    protected:

    private:
};

class IServerFactory
{
    public:
        IServerFactory(){}
        virtual ~IServerFactory(){}

        virtual Corrade::Containers::Pointer<IServer> Create(IServerReceiver & receiver, int portNum, int portNumBusy = 0) = 0;

    protected:

    private:
};

#endif // ISERVER1_H
