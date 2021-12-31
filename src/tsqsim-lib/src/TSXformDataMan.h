#ifndef TSXFORMDATAMAN_H
#define TSXFORMDATAMAN_H

#include "TSRes.h"

#include <Statistical/Matrix.hpp>
#include <Util/VecD.hpp>

class TSXformDataMan
{
    public:
        TSXformDataMan();
        virtual ~TSXformDataMan();

        void Add(const TSRes & tsres);
        int Len() const;

        EnjoLib::VecD converted;
        EnjoLib::Matrix convertedLost;

    protected:

    private:
};

#endif // TSXFORMDATAMAN_H
