#ifndef DATATECH_H
#define DATATECH_H

#include <Util/VecF.hpp>
#include "StochData.h"

class DataTech
{
    public:
        DataTech();
        virtual ~DataTech();

        EnjoLib::VecF maFast, maSlow, maUsedSlow, maUsedFast;
        StochData m_stoch;

    protected:
    private:
};

#endif // DATATECH_H
