#include "SRDummy.h"

#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>
#include <STD/Map.hpp>

SRDummy::SRDummy()
: m_sup(new std::multimap<float, SRFinal>())
, m_res(new std::multimap<float, SRFinal>())
{
    //ctor
}

SRDummy::~SRDummy()
{
    //dtor
}

EnjoLib::Array<SRFinal> SRDummy::GetLevels(const State & st, float bound1, float bound2, const SRFilterHolder * filter) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::GetLowerThan(const State & st, float lowerBound, const SRFilterHolder * filter) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::GetHigherThan(const State & st, float higherBound, const SRFilterHolder * filter) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::FilterBrokenOnly(const EnjoLib::Array<SRFinal> & levels) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::SortClosestFurthest(Direction dir, const EnjoLib::Array<SRFinal> & levels) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::Reverse(const EnjoLib::Array<SRFinal> & levels) const { return EnjoLib::Array<SRFinal>(); }
EnjoLib::Array<SRFinal> SRDummy::Fewer(const EnjoLib::Array<SRFinal> & levels, int maxNumElements) const { return EnjoLib::Array<SRFinal>(); }
