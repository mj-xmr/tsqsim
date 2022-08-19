#ifndef DTWIDISTCOMP_H
#define DTWIDISTCOMP_H

#include <Template/CorradePointerFwd.h>
#include <Util/VecFwd.hpp>

enum class DTWDistType;

class DTWIDistComp
{
    public:
        DTWIDistComp();
        virtual ~DTWIDistComp();
        
        virtual double Compare(const EnjoLib::VecD & obsVec) const = 0;
        
        static CorPtr<DTWIDistComp> Create(const DTWDistType & type, const EnjoLib::VecD & obsNew);

    protected:

    private:
};

#endif // DTWIDISTCOMP_H
