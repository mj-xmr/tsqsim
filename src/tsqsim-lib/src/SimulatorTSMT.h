#ifndef SIMULATORTSMT_H
#define SIMULATORTSMT_H

#include "typesVec.h"
#include "SimulatorTS.h"
#include <Util/VecD.hpp>
#include <Template/ArrayFwd.hpp>

class TSInput;
class TSRes;
class SimulatorTSMT
{
    public:
        SimulatorTSMT();
        virtual ~SimulatorTSMT();

        static void PrintExperimental(const TSInput & tsin, const EnjoLib::VecD & data, const EnjoLib::Str & descr, const EnjoLib::Array<const EnjoLib::VecD *> & plots);

        static STDFWD::vector<TSRes> GetRetsMT(const STDFWD::vector<SimulatorTS::Inp> input);

    protected:

    private:
};

#endif // SIMULATORTSMT_H
