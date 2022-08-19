#ifndef MATPLOTACF_H
#define MATPLOTACF_H

#include <Util/Str.hpp>
#include <Util/VecFwd.hpp>

class MatplotACF
{
    public:
        MatplotACF();
        virtual ~MatplotACF();

        void Plot(const EnjoLib::VecD & dat, int lags, int periodSeasonal, const EnjoLib::Str & title = "") const;
        void Plot(const EnjoLib::VecD & dat, const EnjoLib::Str & title = "") const;

    protected:

    private:
};

#endif // MATPLOTACF_H
