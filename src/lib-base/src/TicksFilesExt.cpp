#include "TicksFilesExt.h"
#include "ConfigDirs.h"
#include "ConfigSym.h"
#include "ConfigMan.h"

#include <EnjoLibBoost/Filesystem.hpp>

#include <Util/FileUtils.hpp>

using namespace std;

TicksFilesExt::TicksFilesExt(EnjoLib::Str symbolName, EnjoLib::Str fileName, EnjoLib::Str periodName, EnjoLib::Str typeName)
{
    EnjoLib::Str perSuffix;
    if (!periodName.empty())
        perSuffix = '-' + periodName;

    EnjoLib::Str typeSuffix;
    if (!typeName.empty())
        typeSuffix = '-' + typeName;

    const ConfigDirs cfg;
    const EnjoLib::Str symbolPer = fileName + perSuffix + typeSuffix;
    const EnjoLib::Str dirBase   = gcfgMan.cfgSym->GetDataBinDir();
    const EnjoLib::Str fileBase  = gcfgMan.cfgSym->GetDataSrcDir() + symbolPer;
    const EnjoLib::Str fileExt   = gcfgMan.cfgSym->GetDataExt();
    //const EnjoLib::Str archiveFmt = ".gz";
    const EnjoLib::Str archiveFmt = cfg.EXT_ARCHIVE;

    EnjoLib::Str dirBin = dirBase + symbolName + "/";
    binaryFile = dirBin   + symbolPer + ".bin";
    textFile   = fileBase + fileExt;
    txtGZipFile = textFile + ".gz";
    txtZipFile  = textFile + ".zip";
    binZipFile = binaryFile + archiveFmt;

    EnjoLib::Filesystem().CreateDirIfNotExists(dirBin);
}

TicksFilesExt::~TicksFilesExt(){}


