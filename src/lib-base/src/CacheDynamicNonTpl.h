#ifndef CACHEDYNAMICNONTPL_HPP
#define CACHEDYNAMICNONTPL_HPP

#include <Util/Str.hpp>
#include <exception>

class IDataProvider;
class CacheDynamicNonTpl
{
    public:
        CacheDynamicNonTpl(const EnjoLib::Str & name, const IDataProvider & data);
        virtual ~CacheDynamicNonTpl();

        EnjoLib::Str GetFilename() const;
        bool FileExists() const;
        void Stored();
        void Add();
        bool ShouldStore() const;
        bool ShouldRestore() const;
        void LogNotFound(const EnjoLib::Str & key) const;
        void Cout(const char * idd, const std::exception & ex) const;

        EnjoLib::Str m_name;
        EnjoLib::Str m_sym;
        EnjoLib::Str m_per;

        bool m_isBinary = true;
        bool m_isMT = true;
        bool m_isRandomBars = false;
        bool m_isTicks = false;
        int m_storeCount = 0;
        mutable int m_counterCout = 0;
    protected:
        
        bool ShouldWorkSettings() const;

    private:
};

#endif // CACHEDYNAMICNONTPL_HPP
