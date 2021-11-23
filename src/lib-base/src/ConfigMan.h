#ifndef CONFIGMAN_H
#define CONFIGMAN_H

#include "OptionsNumeric.h"
#include <Template/CorradePointer.h>
#include <Util/Str.hpp>
#include <Util/VecF.hpp>
#include <Util/Pimpl.hpp>

class ConfigTF;
class ConfigTF2;
class ConfigTS;
class ConfigSym;
class ConfigOpti;
class ConfigQT;
class ConfigQTPlot;
class ConfigML;
class IConfig;
class ConfigTxt;

class ConfigMan
{
    public:
        ConfigMan();
        virtual ~ConfigMan();

        void InitReset();
        void Read();
        void Read(const EnjoLib::Str & str);
        EnjoLib::Str GetConfigString() const;
        void FromOptsNumeric(const OptionsNumeric & opts);
        bool IsMT(bool additionalCondition = true) const;

        float Get(const EnjoLib::Str & idd, float valDefault) const;
        EnjoLib::VecF GetV(const EnjoLib::Str & idd, const EnjoLib::VecF & valDefault) const;

        Corrade::Containers::Pointer<ConfigOpti> cfgOpti;
        Corrade::Containers::Pointer<ConfigQT> cfgQT;
        Corrade::Containers::Pointer<ConfigQTPlot> cfgQTPlot;
        Corrade::Containers::Pointer<ConfigTF> cfgTF;
        Corrade::Containers::Pointer<ConfigTF2> cfgTF2;
        Corrade::Containers::Pointer<ConfigSym> cfgSym;
        Corrade::Containers::Pointer<ConfigTS> cfgTS;
        Corrade::Containers::Pointer<ConfigML> cfgML;
        mutable Corrade::Containers::Pointer<ConfigTxt> cfgTxt;
    protected:

        template <class CFG>
        void InitCfg(CFG * cfg, Corrade::Containers::Pointer<CFG> * ptrVar);

    private:
        bool m_configRead = false;
        static const char m_sep = ';';

        PIMPL
};

extern ConfigMan gcfgMan;

#endif // CONFIGMAN_H
