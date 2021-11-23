#include "ITaAlgoVec.h"
#include "ITaAlgo.h"

#include <Util/VecF.hpp>
#include <STD/VectorCpp.hpp>


using namespace std;
using namespace EnjoLib;

ITaAlgoVec::ITaAlgoVec(){}
ITaAlgoVec::~ITaAlgoVec(){}

EnjoLib::Array<EnjoLib::VecF> ITaAlgoVec::VecDiffsSpeed(const EnjoLib::Array<EnjoLib::VecF> & vecIn)
{
    std::vector<EnjoLib::VecF> ret;
    for (unsigned i = 0; i < vecIn.size(); ++i)
    {
        const EnjoLib::VecF & data = vecIn.at(i);
        const EnjoLib::VecF & diffVec = EnjoLib::VecF(data).Diffs();
        ret.push_back(diffVec);
    }

    return ret;
}

EnjoLib::Array<EnjoLib::VecF> ITaAlgoVec::VecDiffsBetweenEach(const EnjoLib::Array<EnjoLib::VecF> & vecIn)
{
    std::vector<EnjoLib::VecF> ret;
    for (unsigned i = 1; i < vecIn.size(); ++i)
    {
        const EnjoLib::VecF & lower = vecIn.at(i-1);
        const EnjoLib::VecF & highr = vecIn.at(i);
        EnjoLib::VecF diffVec;
        for (unsigned j = 0; j < highr.size() && j < lower.size(); ++j)
        {
            const float diff = lower.at(j) - highr.at(j);
            diffVec.push_back(diff);
        }
        ret.push_back(diffVec);
    }
    return ret;
}

EnjoLib::Array<EnjoLib::VecF> ITaAlgoVec::VecLogs(const EnjoLib::Array<EnjoLib::VecF> & vecIn)
{
    std::vector<EnjoLib::VecF> ret;
    for (unsigned i = 0; i < vecIn.size(); ++i)
    {
        const EnjoLib::VecF & data = vecIn.at(i);
        const EnjoLib::VecF & diffVec = EnjoLib::VecF(data).LogSigned();
        //cout << EnjoLib::VecF(data).PrintScilab("orig");
        //cout << EnjoLib::VecF(diffVec).PrintScilab("Log");
        ret.push_back(diffVec);
    }
    
    return ret;
}