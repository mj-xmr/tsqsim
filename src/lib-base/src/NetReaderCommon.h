#ifndef NETREADERCOMMON_H
#define NETREADERCOMMON_H

namespace EnjoLib
{
    class VecD;
}

#include <Util/Str.hpp>

class NetReaderCommon
{
    public:
        NetReaderCommon();
        virtual ~NetReaderCommon();

        static EnjoLib::Str GetInitialString(const EnjoLib::Str & topic);
        static EnjoLib::Str GetObs1DirString(const EnjoLib::VecD & data);

    protected:

    private:
};

#endif // NETREADERCOMMON_H
