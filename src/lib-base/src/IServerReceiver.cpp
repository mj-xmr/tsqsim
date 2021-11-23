#include "IServerReceiver.h"

// 2000 to max minorow, ale 5100 to max majorow
const unsigned IServerReceiver::SZ_BUF = 5100; /// TODO: nieparzystym SZ mozna odtworzyc bug niepasującego filtra candles
//const unsigned IDataAnalyzerSR::SZ_BUF = StrategySvmPy::LOOKBACK;