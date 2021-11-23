#include "VecFiltersTpl.h"


VecFiltersTpl::VecFiltersTpl()
{
    //ctor
}

VecFiltersTpl::~VecFiltersTpl()
{
    //dtor
}

EnjoLib::VecD VecFiltersTpl::Smooth(const EnjoLib::VecD & inp, int smoothPer) const
{
    if (smoothPer < 1)
        return inp;
    if (smoothPer > int(inp.size()))
        return inp;
    EnjoLib::VecD ret;
    for (int i = 0; i < int(inp.size()); ++i)
    {
        if (i < smoothPer)
            ret.push_back(inp.at(i));
        else
        {
            float smoothSum = 0;
            for (int j = i - smoothPer; j <= i; ++j)
            {
                smoothSum += inp.at(j);
            }
            const float avg = smoothSum / float(smoothPer);
            ret.push_back(avg);
        }
    }
    return ret;
}