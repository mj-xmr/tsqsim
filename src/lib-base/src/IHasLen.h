#ifndef IHASLEN_H
#define IHASLEN_H


class IHasLen
{
    public:
        IHasLen();
        virtual ~IHasLen();
        
        virtual int Len() const = 0;

    protected:

    private:
};

#endif // IHASLEN_H
