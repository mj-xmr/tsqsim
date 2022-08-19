#ifndef SERIALIZATIONSPEC_H
#define SERIALIZATIONSPEC_H

//#include <EnjoLibBoost/Serialization.hpp> // just for testing
//template < typename Ticks > class Serialization; // Forward declaration of template
#include <Util/StrFwd.hpp>
class Ticks;
class HmmStates;
class SerializationSpec// : public Serialization<Ticks>
{
    public:
        SerializationSpec();
        virtual ~SerializationSpec(){}

        void ArchiveZipped(const EnjoLib::Str & serializedFileName, const Ticks & t) const;
        Ticks RestoreZipped(const EnjoLib::Str & serializedFileName) const;
        Ticks Restore(const EnjoLib::Str & serializedFileName) const;
        void Archive(const EnjoLib::Str & serializedFileName, const Ticks & t) const;

        /*
        void ArchiveZipped(const EnjoLib::Str & serializedFileName, const HmmStates & t) const;
        HmmStates RestoreZippedStates(const EnjoLib::Str & serializedFileName) const;
        HmmStates RestoreStates(const EnjoLib::Str & serializedFileName) const;
        void Archive(const EnjoLib::Str & serializedFileName, const HmmStates & t) const;
        */
    protected:
    private:
};

#endif // SERIALIZATIONSPEC_H
