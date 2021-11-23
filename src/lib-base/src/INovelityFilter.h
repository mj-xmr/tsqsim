#ifndef INOVELITYFILTER_H
#define INOVELITYFILTER_H

#include "Direction.h"
namespace EnjoLib
{
    class VecD;
    class Matrix;
}

class INovelityFilter
{
    public:
        INovelityFilter(){}
        virtual ~INovelityFilter(){}

        virtual bool Filter(Direction dir, const EnjoLib::Matrix & train, const EnjoLib::VecD & test) const = 0;

    protected:

    private:
};

#endif // INOVELITYFILTER_H
