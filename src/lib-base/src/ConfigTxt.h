#ifndef CONFIGTXT_HPP
#define CONFIGTXT_HPP

#include "ConfigBase.h"

#include <Template/CacheRAMBase.hpp>
#include <Util/VecF.hpp>

class ConfigTxt : public ConfigBase
{
    public:
        ConfigTxt();
        virtual ~ConfigTxt();
        
        EnjoLib::Str GetConfigString() const override;     
        void FromOptsNumeric(const OptionsNumeric & optsNum) override;
        
        using Key = EnjoLib::Str;
        using Val = float;
        using ValVec = EnjoLib::VecF;
        
        void AddToMissing(const Key & key, const Val & val);
        void AddToMissing(const Key & key, const ValVec & val);
        
        using MapF = EnjoLib::CacheRAMBase<Key, Val>;
        using MapV = EnjoLib::CacheRAMBase<Key, ValVec>;
        
        const MapF & Get()  const;
        const MapV & GetV() const;
        
        MapF & GetRW();
        MapV & GetVRW();

    protected:
        EnjoLib::Str GetFileNameProt() const override;
        
        void RegisterAndReadBools   (EnjoLib::Istream & ifs) override;
        void RegisterAndReadInts    (EnjoLib::Istream & ifs) override;
        void RegisterAndReadFloats  (EnjoLib::Istream & ifs) override;
        void RegisterAndReadStrs    (EnjoLib::Istream & ifs) override;
        
        void RegisterAndReadFloatMap(EnjoLib::Istream & ifs) override;

    private:
        EnjoLib::Str GenCommentLine() const;
        
        EnjoLib::SafePtr<MapF> m_map;
        EnjoLib::SafePtr<MapV> m_mapVec;
        
        EnjoLib::SafePtr<MapF> m_mapMissing;
        EnjoLib::SafePtr<MapV> m_mapVecMissing;
        
        static const char m_comment;
        static const char m_delim;
};

#endif // CONFIGTXT_HPP
