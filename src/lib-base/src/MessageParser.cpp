#include "MessageParser.h"

#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/StackTrace.hpp>

#include <Ios/Osstream.hpp>

using namespace EnjoLib;
using namespace std;

MessageParser::MessageParser(){}

EnjoLib::Str MessageParser::Parse(const EnjoLib::Str & msg)
{
    this->msg = msg;
    CharManipulations cm;
    Tokenizer tok;
    const VecStr & main = tok.Tokenize(msg, '|');
    EnjoLib::Str err;
    try {
        err = symbol = main.at(0);
        err = period = main.at(1);
        // 2 is tick count
        err = command = main.at(3);
        err = tickStr = main.at(4);

        symbolPeriodKey = symbol + "-" + period;
        const int iDataStart = 5;
        const EnjoLib::Str & data = err = main.at(iDataStart);
        varsStr = data;
        const VecStr dataTokenized = tok.Tokenize(data, ';');
        for (const Str & str : dataTokenized)
        {
            err = str;
            double var = cm.ToDouble(str);
            vars.push_back(var);
            //cout << "var " <<  var << endl;
        }
        if (cm.Contains(command, "+"))
        {
            // Command contains strategy name
            const VecStr commandTokenized = tok.Tokenize(command, '+');
            err = command  = commandTokenized.at(0);
            err = strategy = commandTokenized.at(1);
        }

        iperiod = cm.ToDouble(period);
        return "";
    } catch (exception & ex) {
        EnjoLib::Osstream oss;
        oss << "Not enough Tokens (|) = " << main.size() << ", message = \n" << msg << Nl;
        oss << "Last successful = '" << err  << "'" << Nl;
        throw EnjoLib::ExceptInvalidArg(STRACE_RETHROW(ex, oss.str()) );
        //return oss.str();
    }
}

Tick MessageParser::GetTick() const
{
    return Tick(tickStr);
}
