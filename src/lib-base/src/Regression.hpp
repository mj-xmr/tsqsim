#ifndef REGRESSION_H
#define REGRESSION_H

#include <Statistical/RegressionAbstract.hpp>
#include "RegressionRes.h"

#include <Util/VecD.hpp>

#include <Util/Pair.hpp>

namespace EnjoLib {
class Regression : public RegressionAbstract
{
    public:
        Regression();
        virtual ~Regression();

        EnjoLib::VecD polynomialfit(int degree, const EnjoLib::VecD & dx, const EnjoLib::VecD & dy) const override;
        RegressionRes polynomialfitRMS(int degree, const EnjoLib::VecD & dx, const EnjoLib::VecD & dy) const;
        double GetValueForCoeffs(double x, const EnjoLib::VecD & coeff) const;
        EnjoLib::VecD GetValuesForCoeffs(const EnjoLib::VecD & x, const EnjoLib::VecD & coeff) const;

    protected:

    private:
};

}
/*
#define NP 11

double x[] = {0,  1,  2,  3,  4,  5,  6,   7,   8,   9,   10};
double y[] = {1,  6,  17, 34, 57, 86, 121, 162, 209, 262, 321};

#define DEGREE 3
double coeff[DEGREE];

int main()
{
  int i;

  polynomialfit(NP, DEGREE, x, y, coeff);
  for(i=0; i < DEGREE; i++) {
    printf("%lf\n", coeff[i]);
  }
  return 0;
}
*/

#endif // REGRESSION_H
