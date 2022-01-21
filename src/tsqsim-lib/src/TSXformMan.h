#ifndef TSXFORMMAN_H
#define TSXFORMMAN_H

#include "ITSXform.h"
#include "PriceType.h"
#include <Template/CorradePointer.h>
#include <Statistical/Matrix.hpp>
#include <Util/VecStr.hpp>

#include <STD/Vector.hpp>

enum class TSXformType;

class TSRes;
class TSXformMan
{
    public:
        TSXformMan(const PriceType & priceType);
        virtual ~TSXformMan();

        TSRes OnDataPointProt(const IHasCandles & funBase, int idx) const;
        
        EnjoLib::VecD ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const;
        unsigned MaxShift() const;

        void AddXForm(ITSXform * xform);
        void AddXForm(const EnjoLib::Str & namePars);
        void AddXForm(const TSXformType & type, const VecStr & params = {});


    protected:
        //TSRes Reconstruct(double input, const EnjoLib::VecD & lost) const;

    private:
        PriceType m_priceType;
        std::vector<CorPtr<ITSXform>> m_xforms;
};

#endif // TSXFORMMAN_H
