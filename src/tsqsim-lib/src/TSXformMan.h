#ifndef TSXFORMMAN_H
#define TSXFORMMAN_H

#include "ITSXform.h"
#include <Template/CorradePointer.h>
#include <Statistical/Matrix.hpp>
#include <Util/VecStr.hpp>

#include <STD/Vector.hpp>

enum class TSXformType;

class TSRes;
class TSXformMan
{
    public:
        TSXformMan();
        virtual ~TSXformMan();
        
        TSRes OnDataPointProt(const IHasCandles & funBase, int idx) const;
        TSRes Reconstruct(double input, const EnjoLib::VecD & lost) const;
        unsigned MaxShift() const;
        
        void AddXForm(const EnjoLib::Str & namePars);
        void AddXForm(const TSXformType & type, const VecStr & params = {});
        

    protected:

    private:
        
        std::vector<CorPtr<ITSXform>> m_xforms;
};

#endif // TSXFORMMAN_H
