#ifndef IGUIRECEIVER_H
#define IGUIRECEIVER_H

class IDataDisplayer
{
    public:
        IDataDisplayer();
        virtual ~IDataDisplayer();
        virtual void QueueNotification( const char * data ) const = 0;
    protected:
    private:
};

#endif // IGUIRECEIVER_H
