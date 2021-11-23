#include "TradeUtilThin.h"
#include "ConfigDirs.h"
#include "TradeUtil.h"

#include <Util/FileUtils.hpp>
#include <Ios/Ifstream.hpp>
#include <Util/ToolsMixed.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Math/GeneralMath.hpp>

#include <Util/Str.hpp>
#include <Math/GeneralMath.hpp>

using namespace std;
using namespace EnjoLib;

TradeUtilThin::TradeUtilThin()
{
    //ctor
}

TradeUtilThin::~TradeUtilThin()
{
    //dtor
}

void TradeUtilThin::KillPythonServer()
{
    if (not FileUtils().FileExists(ConfigDirs().FILE_PYTHON_SERVER_READY))
        return;

    EnjoLib::Str predictionDir = ConfigDirs().DIR_SCRIPTS + "/prediction/";
    EnjoLib::Str scriptDir = predictionDir + "ensemble/";
    Ifstream flagReady(ConfigDirs().FILE_PYTHON_SERVER_READY);
    EnjoLib::Str pid;
    flagReady >> pid;
    EnjoLib::Str commandKill = "kill " + pid;
    ToolsMixed().SystemCallWarn(commandKill, __PRETTY_FUNCTION__);
}


float TradeUtilThin::CalcGain(float currCap, float gain, float maxCapUsed, float leverage) const{
        return currCap * (1 + gain * leverage * maxCapUsed);
}

float TradeUtilThin::CalcGainNoCap(float currCap, float gain) const {
        return currCap * (1 + gain * 100);
}


int TradeUtilThin::CalcDiffDays(DateInt one, DateInt two) const
{
    CharManipulations cam;
    bool dateOnly = true;
    EnjoLib::Str strDate1 = TradeUtil().Date2Str(one, dateOnly);
    EnjoLib::Str strDate2 = TradeUtil().Date2Str(two, dateOnly);
    //cout << strDate1 << endl;
    //return 12*6 + 3;

    VecStr tok1 = Tokenizer().Tokenize(strDate1, '-');
    VecStr tok2 = Tokenizer().Tokenize(strDate2, '-');
    int year1  = cam.ToInt(tok1.at(0));
    int month1 = cam.ToInt(tok1.at(1));
    int day1 = cam.ToInt(tok1.at(2));
    int year2  = cam.ToInt(tok2.at(0));
    int month2 = cam.ToInt(tok2.at(1));
    int day2 = cam.ToInt(tok2.at(2));

    int yearsMonthsDays1 = year1 * 12 * 30 + month1 * 30 + day1;
    int yearsMonthsDays2 = year2 * 12 * 30 + month2 * 30 + day2;

    int diff = GeneralMath().Fabs(yearsMonthsDays1 - yearsMonthsDays2);
    return diff;
}

float TradeUtilThin::CalcPeriodTicksRelToHour(int numTicks) const
{
    return 60 / float(numTicks);
}

unsigned TradeUtilThin::GetIdFromPrice(float price) const
{
    const GeneralMath gm;
    const int maxDigitsAll = 6;
    const int numDigits = gm.GetNumDigits(price);
    const int diffDigits = maxDigitsAll - numDigits;
    const unsigned idd = static_cast<unsigned>(gm.round(price * gm.PowInt(10, diffDigits)));
    return idd;
}

unsigned TradeUtilThin::ConvertIndexConst(unsigned i, unsigned size) const
{
    return ConvertIndex(i, size);
}

