#include "ConfigDirs.h"
#include <Util/Str.hpp>
#include <Util/ToolsMixed.hpp>

using namespace std;

ConfigDirs::ConfigDirs()
    : DIR_DATA("data/")
    , DIR_DATA_TXT(DIR_DATA + "/data/txt/")
    , DIR_DATA_BIN(DIR_DATA + "/data/bin/")
    , DIR_RAMDISK(EnjoLib::ToolsMixed::GetTmpDir() + "tf/")
    , DIR_CACHE(DIR_DATA + "/cache/")
    , DIR_CFG("cfg/")
    , DIR_SCRIPTS("../scripts/")
    , DIR_OUT(DIR_RAMDISK + "/screenshots")
    //, DIR_OUT(DIR_DATA + "/prod/7")
    , DIR_OUT_LABELS(DIR_DATA + "/labels")
    , DIR_LABELS_RANGE("static/labels-range/")
    , DIR_LABELS_SIGNAL("static/labels-strat/")
    , DIR_CRYPTO("static/crypto/")
    , FILE_LABELS("/labels-strat.txt")
    , FILE_CORREL_LIST(DIR_DATA + "/list_correl.txt")
    , FILE_CRYPTO_STATS("/correl_stats.txt")
    , FILE_CRYPTO_ADAPT("/correl_adapt.txt")
    , FILE_CRYPTO_SPREADS(DIR_CRYPTO + "crypto_spreads_poloniex.csv")
    , FILE_PYTHON_SERVER_READY(DIR_DATA + "/svm/srv-ready.txt")
    , DIR_OPTI_DEVEL(DIR_RAMDISK + "/opti-devel/")
    , DIR_OPTI_RELEASE("static/opti-release/")
    , DIR_FLAGS_MT("/home/enjo/MQL4/Files/")
    , DIR_FLAGS_MT_ARM(DIR_FLAGS_MT + "/FlagsArm/")
    , DIR_FLAGS_MT_OPEN(DIR_FLAGS_MT + "/FlagsMarketOpen/")
    , DIR_FLAGS_MT_CLOSE(DIR_FLAGS_MT + "/FlagsClose/")
    , DIR_ML_SCALING(DIR_DATA + "/ml/scaling/")
    , DIR_ML_BASE(DIR_RAMDISK + "/ml/")
    , FILE_ML_HORI("/hori")
    , DIR_INTEREST(DIR_DATA + "/data/interest/")
    , FILE_INTEREST(DIR_INTEREST + "/interest.txt")
    , EXT_ARCHIVE(".xz")
    //, EXT_ARCHIVE(".zst") // Will get better from 1.4.5
    //, EXT_ARCHIVE(".gz")
{
}

//ConfigDirs ConfigDirs();
