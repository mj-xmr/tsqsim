#ifndef SCOREINPUT_H_INCLUDED
#define SCOREINPUT_H_INCLUDED

#include <Util/VecF.hpp>
#include <Systems/Point.hpp>

struct ScoreInput
{
    EnjoLib::VecF input;
    EnjoLib::Point p1;
    EnjoLib::Point p2;
    float score = 0;
};

#endif // SCOREINPUT_H_INCLUDED
