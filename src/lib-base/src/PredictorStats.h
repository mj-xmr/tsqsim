#ifndef PREDICTORSTATS_H
#define PREDICTORSTATS_H

#include <Util/Str.hpp>
#include <Util/VecD.hpp>

class ITSFun;

struct PredictorStatsRes
{
    double rmsBase2Truth = 0;
    double rmsPred2Base = 0;
    double rmsPred2Truth = 0;
    double ratioPred2Base = 0;
    double points = 0;
};

class PredictorStats
{
    public:
        PredictorStats();
        virtual ~PredictorStats();

        PredictorStatsRes GenPoints(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred, int offset = 0) const;
        EnjoLib::Str GenRepNext(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred, int offset = 0) const;
        EnjoLib::Str GenRepNext(const PredictorStatsRes & points) const;

    protected:

    private:
};

#endif // PREDICTORSTATS_H
