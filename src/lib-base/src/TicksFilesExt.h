#ifndef TICKSFILESEXT_H
#define TICKSFILESEXT_H

#include <Util/Str.hpp>

class TicksFilesExt
{
    public:
        TicksFilesExt(EnjoLib::Str symbolName, EnjoLib::Str fileName, EnjoLib::Str periodName = "", EnjoLib::Str typeName = "");
        virtual ~TicksFilesExt();

        EnjoLib::Str binaryFile;
        EnjoLib::Str textFile;
        EnjoLib::Str txtZipFile;
        EnjoLib::Str binZipFile;
    protected:
    private:
};

#endif // TICKSFILESEXT_H
