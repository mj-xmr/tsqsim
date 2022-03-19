#ifndef STRUTIL_H
#define STRUTIL_H

#include "typesStr.h"
#include <Ios/Ostream.hpp>

class StrUtil
{
    public:
        StrUtil();
        virtual ~StrUtil();
        
        void WriteLines(const VecStr & lines, EnjoLib::Ostream & ostr) const;

    protected:

    private:
};

#endif // STRUTIL_H
