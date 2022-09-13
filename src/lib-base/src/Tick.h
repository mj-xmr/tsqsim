#ifndef TICK_H
#define TICK_H

#include <Util/StrFwd.hpp>
#include <3rdParty/stdfwd.hh>
#include <cstdint>
//#include <boost/serialization/access.hpp>
namespace boost
{
    namespace serialization
    {
        class access;
    }
}


/// A tick is a minute!
class Candle;
class Tick
{
    public:
        Tick();
        Tick(const EnjoLib::Str & line);
        virtual ~Tick();


        int GetDayMinute() const;
        Candle ToCandle() const;
        bool IsValid() const;

        /*
        float GetOpen() const;
        float GetClose() const;
        float GetHigh() const;
        float GetLow() const;
        int GetYear() const;
        int GetMonth() const;
        int GetDay() const;
        int GetHour() const;
        int GetMinute() const;
        */
        short year = 0;
        uint8_t month = 0;
        uint8_t day = 0;
        uint8_t hour = 0;
        uint8_t minute = 0;

        float open = 0;
        float close = 0;
        float hi = 0;
        float lo = 0;
        int vol = 0;

        uint64_t YYYYMMDDhhmmss() const;

        //uint64_t YYYYMMDDhhmmss = 0;

    protected:
    private:
        void ParseFromStream(const EnjoLib::Str & line);
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            //ar & YYYYMMDDhhmmss;

            ar & year;
            ar & month;
            ar & day;
            ar & hour;
            ar & minute;

            ar & open;
            ar & close;
            ar & hi;
            ar & lo;
            ar & vol;
        }
};

#endif // TICK_H
