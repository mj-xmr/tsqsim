#include "Regression.hpp"
#include <Statistical/Statistical.hpp>
#include <Statistical/RegressionFactory.hpp>
#include <Util/VecD.hpp>
#include <Util/Timer.hpp>
#include <Math/GeneralMath.hpp>
#include <Template/CorradePointer.h>

//#include <Math/GeneralMath.hpp>


using namespace std;
using namespace EnjoLib;

Regression::Regression(){}
Regression::~Regression(){}

VecD Regression::polynomialfit(int degree, const VecD & dx, const VecD & dy) const
{
    const Timer timer;
    //const RegType type = RegType::REG_GSL;
    const RegType type = RegType::REG_EIGEN;
    //const RegType type = RegType::REG_AFIRE;
    const VecD & res = RegressionFactory().Create(type)->polynomialfit(degree, dx, dy);
    //cout << "Time taken = " << timer.GetElapsedSeconds() << endl;
    return res;
}

RegressionRes Regression::polynomialfitRMS(int degree, const VecD & dx, const VecD & dy) const
{
    RegressionRes res;
    if (degree == 0)
        return res;
    Statistical stat;
    const VecD & coeffs = polynomialfit(degree, dx, dy);
    const EnjoLib::VecD & dyCalc = GetValuesForCoeffs(dx, coeffs);
    const EnjoLib::VecD & vdy(dy);
    res.coeffs = coeffs.Data();
    res.rms = stat.RMSTwo(vdy, dyCalc);
    res.merr = stat.METwo(vdy, dyCalc);
    return res;
}

double Regression::GetValueForCoeffs(double x, const VecD & coeff) const
{
    const GeneralMath gmat;
    double val = 0;
    const unsigned szz = coeff.size();
    for (unsigned i = 0; i < szz; ++i)
        val += coeff[i] * gmat.PowInt(x, i);
    return val;
}

EnjoLib::VecD Regression::GetValuesForCoeffs(const VecD & x, const VecD & coeff) const
{
    const size_t szz = x.size();
    EnjoLib::VecD ret(szz);
    for (unsigned i = 0; i < szz; ++i)
        ret[i] = GetValueForCoeffs(x[i], coeff);
    return ret;
}
