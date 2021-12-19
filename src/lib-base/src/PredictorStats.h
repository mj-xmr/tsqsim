#ifndef PREDICTORSTATS_H
#define PREDICTORSTATS_H

#include <Util/Str.hpp>
#include <Util/VecD.hpp>

class PredictorStats
{
    public:
        PredictorStats();
        virtual ~PredictorStats();
        
        EnjoLib::Str GenRepNext(const EnjoLib::VecD & truth, const EnjoLib::VecD & pred) const;

    protected:

    private:
};

#endif // PREDICTORSTATS_H
