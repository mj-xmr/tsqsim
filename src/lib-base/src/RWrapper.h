#ifndef RWRAPPER_H
#define RWRAPPER_H

#include <Util/VecD.hpp>
#include <Util/Str.hpp>

class RWrapper
{
    public:
        RWrapper();
        virtual ~RWrapper();
        
        static EnjoLib::VecD R_predictVec(const EnjoLib::VecD & vec);
        static void source(const EnjoLib::Str & scriptPath);

    protected:

    private:
};

#endif // RWRAPPER_H
