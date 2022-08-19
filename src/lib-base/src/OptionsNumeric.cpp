#include "OptionsNumeric.h"
#include <Util/Str.hpp>

#include <STD/Map.hpp>

struct OptionsNumericImpl
{
    std::map<EnjoLib::Str, float> data;
};

OptionsNumeric::~OptionsNumeric(){}
OptionsNumeric::OptionsNumeric()
: m_impl(new OptionsNumericImpl())
{
    
}

bool OptionsNumeric::Has(const EnjoLib::Str & key) const
{
    return m_impl->data.count(key);
}

void OptionsNumeric::Add(const EnjoLib::Str & key, float val)
{
    m_impl->data[key] = val;
}
float OptionsNumeric::Get(const EnjoLib::Str & key) const
{
    return m_impl->data.at(key);
}
