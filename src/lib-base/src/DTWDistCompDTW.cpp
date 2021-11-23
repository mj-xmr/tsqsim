#include "DTWDistCompDTW.h"

#include <Statistical/Statistical.hpp>

using namespace std;
using namespace EnjoLib;

DTWDistCompDTW::DTWDistCompDTW(const EnjoLib::VecD & obsNew)
    //const int size = obsNew.size();
    //const int tol = size / 10; // we use the DTW with a tolerance of 10% (size/10)
    : m_filter(obsNew.Data(), obsNew.size()/10)
    {
    }

DTWDistCompDTW::~DTWDistCompDTW(){}

double DTWDistCompDTW::Compare(const EnjoLib::VecD & obsVec) const
{
    double newbest = m_filter.test(obsVec.Data());
    return newbest;
}


double DTWDistCompKNN::Compare(const EnjoLib::VecD & obsVec) const
{
    double newbest = Statistical().RMSTwo(obsNew, obsVec);
    return newbest;
}