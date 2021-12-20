#ifndef ITSFUN_H
#define ITSFUN_H

#include <Util/VecD.hpp>

class TSRes;
class ITSFun
{
    public:
        ITSFun();
        virtual ~ITSFun();

        virtual TSRes OnDataPoint(int idx) const = 0;
        virtual TSRes Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const = 0;
        virtual unsigned Len() const = 0;
        virtual const char * GetName() const = 0;

    protected:

    private:
};

#endif // ITSFUN_H
