#ifndef PATTERNPREPROCESSOR_H
#define PATTERNPREPROCESSOR_H

#include "Direction.h"
#include "XY.h"

#include <Systems/Point.hpp>
#include <Template/Array.hpp>
#include <3rdParty/stdfwd.hh>


class PatternPreprocessor
{
    public:
        PatternPreprocessor(){}
        virtual ~PatternPreprocessor(){}

        EnjoLib::Array<EnjoLib::Point> InvertAndScale(const EnjoLib::Array<XY> & patternData, Direction bullish, float low, float width) const;
        EnjoLib::Array<XY> Invert(EnjoLib::Array<XY> patternData, Direction bullish) const;
        EnjoLib::Array<XY> CenterX(EnjoLib::Array<XY> patternData, int idxMid) const;
        EnjoLib::Array<XY> CenterY(EnjoLib::Array<XY> patternData, Direction bullish, float low) const;
        EnjoLib::Array<XY> ScaleY(EnjoLib::Array<XY> patternData, int idxMid) const;
        EnjoLib::Array<EnjoLib::Point> ScaleX(EnjoLib::Array<EnjoLib::Point> patternData, float longestWidth) const;

    protected:

    private:
        EnjoLib::Array<EnjoLib::Point> ToPoint(const EnjoLib::Array<XY> & patternData) const;
};

#endif // PATTERNPREPROCESSOR_H
