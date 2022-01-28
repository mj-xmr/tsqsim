#ifndef MATPLOTACF_H
#define MATPLOTACF_H

#include <Util/Str.hpp>
#include <Util/VecD.hpp>

class MatplotACF
{
    public:
        MatplotACF();
        virtual ~MatplotACF();

        void Plot(const EnjoLib::VecD & line, int lags, int periodSeasonal, const EnjoLib::Str & title = "") const;

    protected:

    private:
};

#endif // MATPLOTACF_H
