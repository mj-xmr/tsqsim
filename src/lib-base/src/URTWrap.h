#ifndef URTWRAP_H
#define URTWRAP_H

#include <Util/VecFwd.hpp>
#include <Template/CorradePointerFwd.h>

class IURTAlgo
{
    public:
        virtual ~IURTAlgo() {}
        virtual double GetStatistic() = 0;
        virtual void Show() = 0;
};

class URTWrap
{
    public:
        URTWrap();
        virtual ~URTWrap(){}

        double GetStatistic(const EnjoLib::VecD & data, int lags = 0) const;
        void Show(const EnjoLib::VecD & data, int lags = 0) const;
        
        
        CorPtr<IURTAlgo> Create(const EnjoLib::VecD & data, int lags = 0) const;
        

    protected:

    private:
};

#endif // URTWRAP_H
