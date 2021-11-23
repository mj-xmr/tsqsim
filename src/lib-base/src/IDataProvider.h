#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include "types.h"
#include <Util/Str.hpp>

class DataOCHL;
class DataTech;
class MasAdapter;
class Buffer;
class BufferBool;
class BufferCandles;
class BufferType;
class BufferTypeBool;
class ISR;
class IBufferCandles;

class IDataProvider
{
    public:
        virtual DataOCHL GetData(int numBack, int n = 0) const = 0;
        virtual DataTech GetTech(int numBack, int n = 0) const = 0;
        virtual DataOCHL GetDataDate(DateInt dateStart, int n) const = 0;
        virtual DataTech GetTechDate(DateInt dateStart, int n) const = 0;

        virtual Buffer GetBuf(const BufferType & type) const = 0;
        virtual BufferBool GetBufBool(const BufferTypeBool & type) const = 0;
        virtual const IBufferCandles & GetCandles() const = 0;
        virtual float GetClose(int sti) const = 0;
        virtual const ISR & GetSR() const = 0;

        virtual EnjoLib::Str GetName() const = 0;
        virtual EnjoLib::Str GetSymbolName() const = 0;
        virtual EnjoLib::Str GetSymbolPeriodId(char delim = '-') const = 0;
        virtual bool IsMetaTrader() const = 0;

        virtual int Len() const = 0;
        virtual float GetSpread(int sti) const = 0;
        virtual float GetLeverage() const = 0;
        virtual float GetMaxLossPercent() const = 0;

};

#endif // IDATAPROVIDER_H

