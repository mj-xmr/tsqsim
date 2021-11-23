#ifndef OPTIONSNUMERIC_H
#define OPTIONSNUMERIC_H


#include <Template/SafePtr.hpp>
#include <Util/Str.hpp>

struct OptionsNumericImpl;
class OptionsNumeric
{
public:
    OptionsNumeric();
    virtual ~OptionsNumeric();

    bool Has(const EnjoLib::Str & key) const;
    void Add(const EnjoLib::Str & key, float);
    float Get(const EnjoLib::Str & key) const;

    EnjoLib::SafePtr<OptionsNumericImpl> m_impl;

private:
};


#endif // OPTIONSNUMERIC_H
