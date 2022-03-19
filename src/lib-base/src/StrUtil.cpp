#include "StrUtil.h"

StrUtil::StrUtil()
{
    //ctor
}

StrUtil::~StrUtil()
{
    //dtor
}

void StrUtil::WriteLines(const VecStr & lines, EnjoLib::Ostream & ostr) const
{
    for (const EnjoLib::Str & line : lines)
    {
        ostr << line << EnjoLib::Nl;
    }
}
