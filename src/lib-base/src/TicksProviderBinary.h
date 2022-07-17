#ifndef ARCHIVER_H
#define ARCHIVER_H

#include "ITicksProvider.h"
#include <Ios/Istream.hpp>
#include "typesStr.h"

class Ticks;

class TicksProviderBinary : public ITicksProvider
{
    public:
        TicksProviderBinary();
        virtual ~TicksProviderBinary();

        CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbol, const ConfigSym * confSym = nullptr) const override;
        CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;

        virtual VecStr Convert(const VecStr & lines) const;

    protected:

    private:
        CorPtr<ITicks> StoreOrRestore(const EnjoLib::Str & symbol, const EnjoLib::Str & fileName) const;
        void Archive(const EnjoLib::Str & symbol, const Ticks & t) const;
        void ArchiveTickMonth(const EnjoLib::Str & symbol, const Ticks & t, bool isEndl) const;
        CorPtr<ITicks> Restore(const EnjoLib::Str & serializedFileName) const;
        CorPtr<ITicks> RestoreZipped(const EnjoLib::Str & serializedFileName) const;
        CorPtr<ITicks> UnzipTxt(const EnjoLib::Str & symbol, const EnjoLib::Str & fileName, const EnjoLib::Str & txtFileName) const;
        Ticks ReadFile(const EnjoLib::Str & symbolName, EnjoLib::Istream & is) const;
};

#endif // ARCHIVER_H
