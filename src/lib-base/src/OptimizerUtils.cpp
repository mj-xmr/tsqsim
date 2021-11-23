#include "OptimizerUtils.h"
#include "ConfigDirs.h"
#include "IDataProvider.h"
#include <Util/FileUtils.hpp>
#include "TradeUtil.h"
#include "SymbolAlternatives.h"


using namespace std;
using namespace EnjoLib;

OptimizerUtils::OptimizerUtils(){}
OptimizerUtils::~OptimizerUtils(){}

EnjoLib::Str OptimizerUtils::GetVarBaseDir(bool release) const
{
    ConfigDirs cfg;
    if (release)
        return cfg.DIR_OPTI_RELEASE;
    else
    {
        FileUtils().CreateDirIfNotExistsLinux(cfg.DIR_OPTI_DEVEL);
        return cfg.DIR_OPTI_DEVEL;
    }

}

EnjoLib::Str OptimizerUtils::GetVarDir(const IDataProvider & period, bool release) const
{
    const EnjoLib::Str & baseDir = GetVarBaseDir(release);
    EnjoLib::Str sym = period.GetSymbolName();
    sym = TradeUtil().CutSymbolTestingPrefix(sym);
    sym = SymbolAlternatives().Get(sym);
    //cout << "OptimizerUtils::GetVarDir() sym = " << sym  << endl;
    const EnjoLib::Str & dir = baseDir + '/' + sym + '/' + period.GetName() + '/';
    return dir;
}

EnjoLib::Str OptimizerUtils::GetVarPath(const IDataProvider & period, const EnjoLib::Str & varId, bool release) const
{
    const EnjoLib::Str & dir = GetVarDir(period, release);
    const EnjoLib::Str pathVar = dir + '/' + varId + ".txt";
    return pathVar;
}
