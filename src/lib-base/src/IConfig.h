#ifndef ICONFIG_H
#define ICONFIG_H

#include "OptionsNumeric.h"
#include <Util/Str.hpp>
#include <Ios/Istream.hpp>
#include <Template/VecT.hpp>

class IConfig
{
    public:
        IConfig();
        virtual ~IConfig();

        bool Read();
        bool Read(EnjoLib::Istream & ifs);
        bool Read(const EnjoLib::Str & data);
        void Write() const;
        virtual EnjoLib::Str GetConfigString() const = 0;

        virtual void FromOptsNumeric(const OptionsNumeric & optsNum) = 0;
        
        virtual const EnjoLib::VecT<bool*> & GetBools() const = 0;
        virtual const EnjoLib::VecT<EnjoLib::Str> & GetBoolsDescr() const = 0;
        virtual const EnjoLib::VecT<EnjoLib::Str> & GetBoolsToolTip() const = 0;

    protected:
        //virtual void ReadProt(EnjoLib::Istream & ifs) = 0;

        EnjoLib::Str GetFileName() const;
        virtual EnjoLib::Str GetFileNameProt() const = 0;
        virtual EnjoLib::Str GetFileNameProtBackup() const;
        bool PrepareReadStream(EnjoLib::Istream & ifs) const;

        virtual void RegisterAndReadBools(EnjoLib::Istream & ifs) = 0;
        virtual void RegisterAndReadInts(EnjoLib::Istream & ifs) = 0;
        virtual void RegisterAndReadFloats(EnjoLib::Istream & ifs) = 0;
        virtual void RegisterAndReadStrs(EnjoLib::Istream & ifs) = 0;
        virtual void RegisterAndReadFloatMap(EnjoLib::Istream & ifs);

        virtual void RegisterAndReadBool (EnjoLib::Istream & ifs, bool & var, const bool & def, const EnjoLib::Str & descr = "", const EnjoLib::Str & tooltip = "") = 0;
        virtual void RegisterAndReadInt  (EnjoLib::Istream & ifs, long int & var, const long int & def) = 0;
        virtual void RegisterAndReadFloat(EnjoLib::Istream & ifs, float & var, const float & def) = 0;
        virtual void RegisterAndReadStr  (EnjoLib::Istream & ifs, EnjoLib::Str & var, const EnjoLib::Str & def) = 0;
        virtual EnjoLib::Str GetRelDebDirBase(bool isRelease) const = 0;

        virtual void Clear() = 0;
    private:
        
};


#endif // ICONFIG_H
