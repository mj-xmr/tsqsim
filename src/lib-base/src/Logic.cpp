#include "Logic.h"
#include "State.h"

#include <Util/Pair.hpp>
#include <Util/VecD.hpp>
#include <Util/CoutBuf.hpp>
#include <Statistical/Assertions.hpp>
#include <Template/AlgoSTDThin.hpp>
using namespace EnjoLib;

Logic::Logic(){}
Logic::~Logic(){}

bool Logic::GT(double a, double b, const State & st)
{
    Swp(a, b, st);
    return a > b;
}
bool Logic::LT(double a, double b, const State & st)
{
    Swp(a, b, st);
    return a < b;
}
bool Logic::GTE(double a, double b, const State & st)
{
    Swp(a, b, st);
    return a >= b;
}
bool Logic::LTE(double a, double b, const State & st)
{
    Swp(a, b, st);
    return a <= b;
}

double Logic::Add(double a, double b, const State & st)
{
    const double add = b * (st.bullish ? 1 : -1);
    const double ret = a + add;
    return ret;
}

double Logic::Sub(double a, double b, const State & st)
{
    const double sub = b * (st.bullish ? 1 : -1);
    const double ret = a - sub;
    return ret;
}

void Logic::Swp(double & a, double & b, const State & st)
{
    if (not st.bullish)
    {
        //LOGL << "Swapping " << a << " " << b << Nl;
        AlgoSTDThin().Swap(a, b);
    }
    //LOGL << "Swp" << a << " " << b << Nl;
}

bool Logic::VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2, double eps)
{
    /// TODO: epsMust be a percentage! then upstream
    if (data1.size() != data2.size())
    {
        return false;
    }
    for (size_t i = 0; i < data1.size(); ++i)
    {
        if (not DoublesEqual(data1.at(i), data2.at(i), eps))
        {
            return false;
        }
    }
    return true;
}

bool Logic::DoublesEqual(const double data1, const double data2, double eps)
{
    /// TODO: epsMust be a percentage! then upstream
    if (data1 == data2)
    {
        return true;
    }
    VecD vec;
    vec.Add(data1);
    vec.Add(data2);
    const double mean = vec.Mean();
    if (not EnjoLib::Assertions::In(mean - eps, mean, mean + eps))
    {
        return false;
    }
    return true;
}
