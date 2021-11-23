#ifndef ISIMULOBSERVER_H
#define ISIMULOBSERVER_H

class ISimulObserver
{
    public:
        ISimulObserver();
        virtual ~ISimulObserver();
        virtual void SimulNotify(int progress, int sz) = 0;

    protected:

    private:
};

#endif // ISIMULOBSERVER_H
