#ifndef REGRESSIONPARS_H
#define REGRESSIONPARS_H

#include <Util/Str.hpp>

struct RegressionPars
{
    RegressionPars(int past = 0, int future = 0, int degree = 2);

    bool IsValid() const;
    bool IsValidMinLen() const;
    int GetLen() const;
    EnjoLib::Str ToStr() const;
    
    static RegressionPars FromPast(const RegressionPars & pars, int past);
    static RegressionPars FromFuture(const RegressionPars & pars, int future);

    int past = 0;
    int future = 0;
    int degree = 3;

    static const int MIN_LEN;
};

#endif // REGRESSIONPARS_H
