#ifndef TSRES_H
#define TSRES_H

#include <Util/VecD.hpp>

class TSRes
{
    public:
        explicit TSRes(bool valid = false);
        virtual ~TSRes();

        bool valid = false;
        double val = 0;
        EnjoLib::VecD lost;



    protected:

    private:
};

#endif // TSRES_H
