#ifndef DATEPARSER_H
#define DATEPARSER_H

#include <Util/StrFwd.hpp>

class DateParser
{
    public:
        DateParser();
        virtual ~DateParser();
        void Parse(const EnjoLib::Str & dateStr);

        int day, month, year;

    protected:
    private:
};

#endif // DATEPARSER_H
