#include "Distribs.h"

#include <Statistical/StdDev.hpp>
#include <boost/math/distributions/normal.hpp>

using namespace boost::math;

Distribs::Distribs()
{
}

double Distribs::NormalPDF(double mean, const EnjoLib::StdDev & stdDev, double arg) const
{
    auto d = normal_distribution<>(mean, stdDev.GetValue());
    return pdf(d, arg);
}
