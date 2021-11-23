#ifndef RESULTS_H
#define RESULTS_H

#include <Util/Result.hpp>
#include "Candle.h"
#include "State.h"

class ResultCandle : public EnjoLib::Result<Candle>
{
    public:
        ResultCandle(const Candle & value, bool status);
        virtual ~ResultCandle();
    protected:
    private:
};

class ResultState : public EnjoLib::Result<State>
{
    public:
        ResultState(const State & value, bool status);
        virtual ~ResultState();
    protected:
    private:
};

#endif // RESULTS_H
