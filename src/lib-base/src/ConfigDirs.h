#ifndef CONFIGDIRS_H
#define CONFIGDIRS_H

#include <Util/Str.hpp>

class ConfigDirs
{
    public:
        ConfigDirs();
        virtual ~ConfigDirs(){}

        const EnjoLib::Str DIR_DATA;
        const EnjoLib::Str DIR_DATA_TXT;
        const EnjoLib::Str DIR_DATA_BIN;
        const EnjoLib::Str DIR_RAMDISK;
        const EnjoLib::Str DIR_CACHE;
        const EnjoLib::Str DIR_CFG;
        const EnjoLib::Str DIR_SCRIPTS;
        const EnjoLib::Str DIR_SCRIPTS2;
        const EnjoLib::Str DIR_OUT;
        const EnjoLib::Str DIR_OUT_LABELS;
        const EnjoLib::Str DIR_LABELS_RANGE;
        const EnjoLib::Str DIR_LABELS_SIGNAL;
        const EnjoLib::Str DIR_CRYPTO;
        const EnjoLib::Str FILE_LABELS;
        const EnjoLib::Str FILE_CORREL_LIST;
        const EnjoLib::Str FILE_CRYPTO_STATS;
        const EnjoLib::Str FILE_CRYPTO_ADAPT;
        const EnjoLib::Str FILE_CRYPTO_SPREADS;
        const EnjoLib::Str FILE_PYTHON_SERVER_READY;
        const EnjoLib::Str DIR_OPTI_DEVEL;
        const EnjoLib::Str DIR_OPTI_RELEASE;
        const EnjoLib::Str DIR_FLAGS_MT;
        const EnjoLib::Str DIR_FLAGS_MT_ARM;
        const EnjoLib::Str DIR_FLAGS_MT_OPEN;
        const EnjoLib::Str DIR_FLAGS_MT_CLOSE;
        const EnjoLib::Str DIR_ML_SCALING;
        const EnjoLib::Str DIR_ML_BASE;
        const EnjoLib::Str FILE_ML_HORI;
        const EnjoLib::Str DIR_INTEREST;
        const EnjoLib::Str FILE_INTEREST;
        const EnjoLib::Str EXT_ARCHIVE;

    protected:

    private:
};

//extern ConfigDirs ConfigDirs();

#endif // CONFIGDIRS_H
