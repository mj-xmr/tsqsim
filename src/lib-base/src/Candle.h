#ifndef TICKBASE_H
#define TICKBASE_H

#include "types.h"
#include "IHasDateComponents.h"
#include "Direction.h"
#include "PriceData.h"
#include <Util/Str.hpp>

#include <3rdParty/stdfwd.hh>

enum class PriceType;
class State;
class Tick;
class Candle : public IHasDateComponents
{
    public:
        PriceData price;
        
        Candle();
        Candle(const PriceData & price);
        Candle(float open, float close, float hi, float lo); // for unit testing
        virtual ~Candle();
        void UpdateHighLow( const Tick & tick );
        void MakePinbar( const Tick & tick );
        void SetOpen( float o );
        void SetClose( float c );
        void SetHigh( float c );
        void SetLow( float c );
        void SetOpen( const Tick & tick );
        void SetClose( const Tick & tick );
        void SetDate( DateInt date ) { YYYYMMDDhhmmss = date; } // avoid
        bool IsDataValid() const;
        bool IsDataUnchanging() const;

        float GetOpen() const { return price.open; }
        float GetClose() const { return price.close; }
        float GetHigh() const { return price.hi; }
        float GetLow() const { return price.lo; }

        float GetTypical() const;
        float GetWeightedClose() const;

        float GetPriceByType(const PriceType & type) const;

        int   GetVol() const { return vol; }
        float GetExtr(const State & st) const;
        float GetExtrBody(const State & st) const;
        float GetLen() const;
        float GetBodyMin() const;
        float GetBodyMax() const;
        float GetWickHi() const;
        float GetWickLo() const;
        DateInt GetDate() const { return YYYYMMDDhhmmss; }
        DateInt GetDateOpen() const { return YYYYMMDDhhmmssOpen; }
        EnjoLib::Str GetDateStr() const;
        EnjoLib::Str GetDateStrR() const;
        int GetYear() const override { return year; }
        int GetMonth() const override { return month; }
        int GetDay() const override { return day; }
        int GetHour() const override { return hour; }
        int GetMinute() const override { return minute; }
        int GetSecond() const override { return second; }
        Direction GetDir() const;
        bool IsInDir(Direction bullish) const;
        bool IsNeutral() const;

        Tick ToTick() const;
        EnjoLib::Str ToStringTick(const EnjoLib::Str & symbolName) const;
        EnjoLib::Str PrintOCHL() const;
        EnjoLib::Str PrintOHLC() const;

        //float hi = 0;
        //float lo = 0;
        
        

    protected:
    private:

        //float open = 0;
        //float close = 0;

        int vol = 0;

        short year = 0;
        short month = 0;
        short day = 0;
        short hour = 0;
        short minute = 0;
        short second = 0;
        DateInt YYYYMMDDhhmmss = 0;
        DateInt YYYYMMDDhhmmssOpen = 0;
};



#endif // TICKBASE_H
