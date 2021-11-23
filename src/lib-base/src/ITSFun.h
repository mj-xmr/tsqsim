#ifndef ITSFUN_H
#define ITSFUN_H

class TSRes;
class ITSFun
{
    public:
        ITSFun();
        virtual ~ITSFun();
        
        virtual TSRes OnDataPoint(int idx) const = 0;
        virtual unsigned Len() const = 0;

    protected:

    private:
};

#endif // ITSFUN_H
