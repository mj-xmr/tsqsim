#include "SerializationSpec.h"
#include <EnjoLibBoost/Serialization.hpp>

#include <boost/serialization/vector.hpp> // has to be here
#include "Ticks.h"
//#include "HmmStates.h"

using namespace EnjoLib;

SerializationSpec::SerializationSpec(){}

void SerializationSpec::Archive(const EnjoLib::Str & serializedFileName, const Ticks & t) const
{
    Serialization<Ticks>().Archive(serializedFileName.str(), t);
}
void SerializationSpec::ArchiveZipped(const EnjoLib::Str & serializedFileName, const Ticks & t) const
{
    Serialization<Ticks>().ArchiveZipped(serializedFileName.str(), t);
}
Ticks SerializationSpec::Restore(const EnjoLib::Str & serializedFileName) const
{
    return Serialization<Ticks>().Restore(serializedFileName.str());
}
Ticks SerializationSpec::RestoreZipped(const EnjoLib::Str & serializedFileName) const
{
    return Serialization<Ticks>().RestoreZipped(serializedFileName.str());
}

/*
void SerializationSpec::Archive(const EnjoLib::Str& serializedFileName, const HmmStates& t) const
{
    Serialization<HmmStates>().Archive(serializedFileName, t);
}
void SerializationSpec::ArchiveZipped(const EnjoLib::Str& serializedFileName, const HmmStates& t) const
{
    Serialization<HmmStates>().ArchiveZipped(serializedFileName, t);
}
HmmStates SerializationSpec::RestoreStates(const EnjoLib::Str & serializedFileName) const
{
    return Serialization<HmmStates>().Restore(serializedFileName);
}
HmmStates SerializationSpec::RestoreZippedStates(const EnjoLib::Str & serializedFileName) const
{
    return Serialization<HmmStates>().RestoreZipped(serializedFileName);
}
*/

