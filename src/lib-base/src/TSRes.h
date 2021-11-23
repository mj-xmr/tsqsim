#ifndef TSRES_H
#define TSRES_H


class TSRes
{
    public:
        TSRes(bool valid = false);
        virtual ~TSRes();
        
        bool valid = false;
        double val = 0;
        
        

    protected:

    private:
};

#endif // TSRES_H
