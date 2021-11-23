#ifndef CONFIGBASE_H
#define CONFIGBASE_H

#include "IConfig.h"

class ConfigBase : public IConfig
{
    public:
        ConfigBase();
        virtual ~ConfigBase();
        
        EnjoLib::Str GetConfigString() const override;
        const EnjoLib::VecT<bool*> & GetBools() const override;
        const EnjoLib::VecT<EnjoLib::Str> & GetBoolsDescr() const override;
        const EnjoLib::VecT<EnjoLib::Str> & GetBoolsToolTip() const override;

    protected:
        void RegisterAndReadBool (EnjoLib::Istream & ifs, bool & var, const bool & def, const EnjoLib::Str & descr, const EnjoLib::Str & tooltip = "") override;
        void RegisterAndReadInt  (EnjoLib::Istream & ifs, long int & var, const long int & def) override;
        void RegisterAndReadFloat(EnjoLib::Istream & ifs, float & var, const float & def) override;
        void RegisterAndReadStr  (EnjoLib::Istream & ifs, EnjoLib::Str & var, const EnjoLib::Str & def) override;
        EnjoLib::Str GetRelDebDirBase(bool isRelease) const override;

        void Clear() override;
        
        template <class T>
        void UpdateVarIfConfigured(const OptionsNumeric & optsNum, T & var, const EnjoLib::Str & varID);
        
    private:
        template <class T>
        bool RegisterAndRead(EnjoLib::Istream & ifs, EnjoLib::IVecT<T*> & regist, T & var, const T & defaultVal);
        
        EnjoLib::VecT<bool*> m_registeredVarsBool;
        EnjoLib::VecT<EnjoLib::Str> m_registeredVarsBoolDescr;
        EnjoLib::VecT<EnjoLib::Str> m_registeredVarsBoolToolTip;
        EnjoLib::VecT<long int*> m_registeredVarsInt;
        EnjoLib::VecT<float*> m_registeredVarsFloat;
        EnjoLib::VecT<EnjoLib::Str*> m_registeredVarsStr;
};


template <class T>
void ConfigBase::UpdateVarIfConfigured(const OptionsNumeric & optsNum, T & var, const EnjoLib::Str & varID)
{
    if (optsNum.Has(varID))
    {
        var = optsNum.Get(varID);
    }
}

#endif // CONFIGBASE_H
