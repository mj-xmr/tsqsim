#ifndef STARTEND_H
#define STARTEND_H

#include <Util/StrFwd.hpp>

class IStrategy;
class IDataProvider;

struct StartEnd
{
    StartEnd(int start = 0, int end = 0);
    bool IsValid() const;

    bool operator== (const StartEnd & other) const;

    //StartEnd ConvertIndexes(const IDataProvider & hasLen) const; // Probably wrong, since more data, than there's tech indicators!
    StartEnd ConvertIndexes(const IStrategy & hasLen) const;
    EnjoLib::Str ToStr() const;
    void FromStr(const EnjoLib::Str & str);

    int start = 0;
    int end = 0;

};

#endif // STARTEND_H
