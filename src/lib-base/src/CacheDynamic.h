#ifndef CACHEDYNAMIC_H
#define CACHEDYNAMIC_H

#include "CacheDynamicNonTpl.h"

#include <Template/CacheRAMBase.hpp>
#include <Template/SafePtr.hpp>

class IDataProvider;

template <class T>
class CacheDynamic
{
    public:
        CacheDynamic(const EnjoLib::Str & name, const IDataProvider & data);
        virtual ~CacheDynamic();

        const T * Get(const EnjoLib::Str & key) const;
        const T & Add(const EnjoLib::Str & key, const T & val);
        EnjoLib::Str GetFilename() const;
        EnjoLib::Str GetName() const;

    protected:

    private:
        CacheDynamicNonTpl nonTpl;
        bool m_binary = true;
        bool m_portable = true;
        //mutable int m_counterCout = 0;

        using Cache = EnjoLib::CacheRAMBase<EnjoLib::Str, T>;

        EnjoLib::SafePtr<Cache> m_cache;
};

#endif // CACHEDYNAMIC_H
