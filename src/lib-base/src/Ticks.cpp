#include "Ticks.h"
#include "Candle.h"

#include <Ios/Ifstream.hpp>
#include <Util/Timer.hpp>
#include <Util/LoopThreaded.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/CoutBuf.hpp>
#include <Template/LoopThreadedTpl.hpp>

using namespace std;
using namespace EnjoLib;

Ticks::Ticks(){}
Ticks::~Ticks(){}

static Tick GetTick(const Str & s)
{
    //cout << "GetTick() " << s << "\n";
    return Tick(s);
}

Ticks::Ticks(const std::vector<Tick> & ticks)
: m_ticks(ticks)
{
}

Ticks::Ticks(const IIterableConst<Tick> & ticks)
{
    for (const Tick & t : ticks)
        Add(t);
}

Ticks::Ticks(const ITicks & ticks)
: Ticks(ticks.GetTicks3())
{

}

Ticks::Ticks(const EnjoLib::Str & symbolName, const VecStr & lines, bool skipHeader)
{
    //LoopThreadedTpl<string, Tick> loopThreadedTpl(lines.size(), &GetTick);
    //loopThreadedTpl.AddInputVector(lines); // Alternative without the filtering
    //m_ticks = loopThreadedTpl.AddInputVectorGetOutputVector(lines); // Alternative without the filtering
    //{ LOGL << symbolName << ": Adding to vector\n"; }
    const CharManipulations cmp;
    std::vector<Str> filtered;
    const int startIdx = skipHeader ? 1 : 0;
    //copy(lines.begin() + startIdx, lines.end(), std::back_inserter(filtered));


    for( int i = 0; i < int(lines.size()); ++i )
    {
        if (skipHeader)
        {
            skipHeader = false;
            continue;
        }
        //const string & lineStripped = cmp.Trim(lines[i]);
        //if (lineStripped.empty())
        {
          //  continue;
        }
        //cout << lineStripped << endl;
        //loopThreadedTpl.AddInput(i, lineStripped); // Buggy!
        //m_ticks.dat.push_back(GetTick(lines[i]));
        filtered.push_back(lines[i]);
    }
    //{ LOGL << symbolName << ": Calculating\n"; }
    std::function<decltype(GetTick)> f_conv = &GetTick;
    m_ticks = ConvertVectorThreaded(filtered, f_conv);
    //m_ticks = loopThreadedTpl.GetOutputVector();
}

Ticks::Ticks(const EnjoLib::Str & symbolName, const EnjoLib::Str & fileName, size_t numLines, bool skipHeader)
{
    Ifstream is(fileName);
    *this = Ticks(symbolName, is, numLines, skipHeader);
}

Ticks::Ticks(const EnjoLib::Str & symbolName, EnjoLib::Istream & is, size_t numLines, bool skipHeader)
{
    m_ticks.dat.clear();
    Str line;
    if (skipHeader)
        GetLine(is, line);
    while (GetLine(is, line))
    {
        m_ticks.dat.push_back(Tick(line));
        m_progressMonit.PrintProgressBarTime(m_ticks.dat.size(), numLines, symbolName, true);
    }
}

CorPtr<ITicks> Ticks::FromYear(int year) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
        if (tick.year >= year)
            filtered.m_ticks.dat.push_back(tick);
    return CorPtr<ITicks>(new Ticks(filtered));
}

CorPtr<ITicks> Ticks::TillYear(int year) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
        if (tick.year <= year)
            filtered.m_ticks.dat.push_back(tick);
    return CorPtr<ITicks>(new Ticks(filtered));
}

CorPtr<ITicks> Ticks::BetweenYears(int yearStart, int yearEnd) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
        if (yearStart <= tick.year && tick.year <= yearEnd)
            filtered.m_ticks.dat.push_back(tick);
    return CorPtr<ITicks>(new Ticks(filtered));
}

CorPtr<ITicks> Ticks::FromMonth(int month, int year) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
    {
        if (tick.year > year)
            filtered.m_ticks.dat.push_back(tick);
        else
            if (tick.month >= month)
                filtered.m_ticks.dat.push_back(tick);
    }
    return CorPtr<ITicks>(new Ticks(filtered));
}

CorPtr<ITicks> Ticks::TillMonth(int month, int year) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
    {
        if (tick.year < year)
            filtered.m_ticks.dat.push_back(tick);
        else
            if (tick.month <= month)
                filtered.m_ticks.dat.push_back(tick);
    }
    return CorPtr<ITicks>(new Ticks(filtered));
}

CorPtr<ITicks> Ticks::DeleteMonth(int month, int year) const
{
    Ticks filtered;
    for(const Tick & tick : m_ticks)
    {
        if (tick.year == year && tick.month == month)
        {
            // Will be cut out
        }
        else
        {
            filtered.m_ticks.dat.push_back(tick);
        }
    }
    return CorPtr<ITicks>(new Ticks(filtered));
}

bool Ticks::HasMonth(int month, int year) const
{
    for(const Tick & tick : m_ticks)
    {
        if (tick.year == year && tick.month == month)
        {
            return true;
        }
    }
    return false;
}

VecCan Ticks::ToCandles() const
{
    VecCan candles;
    candles.reserve(m_ticks.dat.size());
    for (const Tick & t : m_ticks)
    {
        candles.push_back(t.ToCandle());
    }
    return candles;
}

void Ticks::Add(const ITicks & ticks)
{
    for (const Tick & tick : ticks)
        Add(tick);
}

void Ticks::Set(const ITicks & ticks)
{
    m_ticks.dat.clear();
    Add(ticks);
}

void Ticks::Add(const Tick & tick)
{
    if (not tick.IsValid())
        return;
    m_ticks.dat.push_back(tick);
}

const Tick & Ticks::at(size_t idx) const
{
    return m_ticks.dat.at(idx);
}

size_t Ticks::size() const
{
    return m_ticks.dat.size();
}

Ticks::const_iterator Ticks::begin() const    {return const_iterator(&m_ticks.dat[0]);}
Ticks::const_iterator Ticks::end()   const    {return const_iterator(&m_ticks.dat[m_ticks.dat.size()]);}
Ticks::const_iterator Ticks::cbegin() const   {return begin();}
Ticks::const_iterator Ticks::cend()   const   {return end();}
