#include "PatternPreprocessor.h"
#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

EnjoLib::Array<Point> PatternPreprocessor::InvertAndScale(const EnjoLib::Array<XY> & patternData, Direction bullish, float low, float width) const
{
    const int IDX_MID = 3;
    EnjoLib::Array<Point> ret;
    EnjoLib::Array<XY> vxy;
    vxy = Invert(patternData, bullish);
    vxy = CenterX(vxy, IDX_MID);
    vxy = CenterY(vxy, bullish, low);
    vxy = ScaleY (vxy, IDX_MID);
    ret = ToPoint(vxy);
    ret = ScaleX (ret, width);
    return ret;
}
EnjoLib::Array<XY> PatternPreprocessor::Invert(EnjoLib::Array<XY> vxy, Direction bullish) const
{
    for (XY & xyy : vxy)
    {
        xyy.x = -xyy.x;
        if (bullish) xyy.y = -xyy.y;
    }
    return vxy;
}

EnjoLib::Array<XY> PatternPreprocessor::CenterX(EnjoLib::Array<XY> vxy, int idxMid) const
{
    int midArg = vxy.at(idxMid).x;
    for (XY & xyy : vxy)
        xyy.x -= midArg;
    return vxy;
}

EnjoLib::Array<XY> PatternPreprocessor::CenterY(EnjoLib::Array<XY> vxy, Direction bullish, float low) const
{
    if (bullish)
        low = -low;
    for (XY & xyy : vxy)
        xyy.y -= low;

    return vxy;
}

EnjoLib::Array<Point> PatternPreprocessor::ScaleX(EnjoLib::Array<Point> vxy, float longestWidth) const
{
    for (Point & xyy : vxy)
        xyy.x /= longestWidth / 2.0;
    return vxy;
}

EnjoLib::Array<XY> PatternPreprocessor::ScaleY(EnjoLib::Array<XY> vxy, int idxMid) const
{
    float midVal = vxy.at(idxMid).y;
    for (XY & xyy : vxy)
        xyy.y /= midVal;
    return vxy;
}

EnjoLib::Array<EnjoLib::Point> PatternPreprocessor::ToPoint(const EnjoLib::Array<XY> & vxy) const
{
    std::vector<Point> ret;
    for (const XY & xyy : vxy)
        ret.push_back(Point(xyy.x, xyy.y));
    return ret;
}
