#ifndef TICKS_H
#define TICKS_H

#include "ITicks.h"
#include "typesVec.h"
#include <Util/VecStr.hpp>
#include <Ios/Istream.hpp>
#include <Template/VectorViewable.hpp>
#include <STD/Vector.hpp>
#include <3rdParty/stdfwd.hh>

#include "Tick.h"
#include <Util/ProgressMonitHigh.hpp>

#include <Template/CorradePointer.h>

class Ticks : public ITicks
{
public:
    Ticks();
    Ticks(const EnjoLib::Str & symbolName, EnjoLib::Istream & is, size_t numLines = 0, bool skipHeader = true);
    Ticks(const EnjoLib::Str & symbolName, const EnjoLib::Str & fileName, size_t numLines = 0, bool skipHeader = true);
    Ticks(const EnjoLib::Str & symbolName, const VecStr & lines, bool skipHeader = true);
    Ticks(const stdfwd::vector<Tick> & ticks);
    Ticks(const ITicks & ticks);
    Ticks(const IIterableConst<Tick> & ticks);
    virtual ~Ticks();

    const std::vector<Tick> & GetTicks3() const override {return m_ticks.dat;}
    EnjoLib::View<Tick> GetTicksView() const override { return EnjoLib::View<Tick>(m_ticks); }
    CorPtr<ITicks> FromYear(int year) const override;
    CorPtr<ITicks> TillYear(int year) const override;
    CorPtr<ITicks> BetweenYears(int yearStart, int yearEnd) const override;
    CorPtr<ITicks> FromMonth(int month, int year) const override;
    CorPtr<ITicks> TillMonth(int month, int year) const override;
    CorPtr<ITicks> DeleteMonth(int month, int year) const override;
    bool HasMonth(int month, int year) const override;
    void Set(const ITicks & ticks) override;
    void Add(const ITicks & ticks) override;
    void Add(const Tick & tick) override;

    VecCan ToCandles() const override;
    
    const Tick & at(size_t idx) const override;
    size_t size() const override;
    
    IITER_IMPL_CONST

private:
    EnjoLib::VectorViewable<Tick> m_ticks;
    EnjoLib::ProgressMonitHigh m_progressMonit;

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_ticks.dat;
    }
};

#endif // TICKS_H
