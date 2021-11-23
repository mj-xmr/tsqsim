#ifndef DTWDISTCOMPDTW_H
#define DTWDISTCOMPDTW_H

#include "DTWIDistComp.h"
#include <Util/VecD.hpp>

#include "dtw.h"

class DTWDistCompDTW : public DTWIDistComp
{
public:
    DTWDistCompDTW(const EnjoLib::VecD & obsNew);    
    virtual ~DTWDistCompDTW();

    double Compare(const EnjoLib::VecD & obsVec) const override;
    
    private:
        mutable LB_Improved m_filter;
};

class DTWDistCompKNN : public DTWIDistComp
{
public:
    DTWDistCompKNN(const EnjoLib::VecD & obsNew)
    : obsNew(obsNew)
    {
    }

    double Compare(const EnjoLib::VecD & obsVec) const override;

    private:
        const EnjoLib::VecD obsNew;
};

#endif // DTWDISTCOMPDTW_H
