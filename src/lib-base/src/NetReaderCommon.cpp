#include "NetReaderCommon.h"
#include "ConfigGlob.h"

#include <Util/Str.hpp>
#include <Util/VecD.hpp>
#include <Ios/Osstream.hpp>

NetReaderCommon::NetReaderCommon(){}
NetReaderCommon::~NetReaderCommon(){}

EnjoLib::Str NetReaderCommon::GetInitialString(const EnjoLib::Str & topic)
{
    EnjoLib::Osstream oss;
    oss << "http://127.0.0.1:" << gcfg.PORT_PY_SERV << "/?";
    oss << "topic=" << topic << "&";
    return oss.str();
}

EnjoLib::Str NetReaderCommon::GetObs1DirString(const EnjoLib::VecD & data)
{
    EnjoLib::Osstream oss;
    oss << "len=" << data.size() << "&";
    for (int i = 0; i < int(data.size()); ++i)
    {
        oss << "o_" << i << "=" << data.at(i) << "&";
    }
    return oss.str();
}
