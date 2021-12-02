#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <Util/Str.hpp>
#include <Util/VecD.hpp>
#include <Tick.h>

class MessageParser
{
    public:
        MessageParser();
        virtual ~MessageParser(){}

        EnjoLib::Str Parse(const EnjoLib::Str & msg);

        EnjoLib::Str msg;
        EnjoLib::Str symbol, command, tickStr, period, symbolPeriodKey, varsStr;
        EnjoLib::Str strategy = "Dummy";
        EnjoLib::VecD vars;
        int iperiod;

        Tick GetTick() const;

    protected:
    private:
        //Tick tick;

};

#endif // MESSAGEPARSER_H
