#ifndef SIMULATORTSMT_H
#define SIMULATORTSMT_H

#include "typesVec.h"
#include "SimulatorTS.h"
#include <Util/VecD.hpp>

class TSInput;
class TSRes;
class SimulatorTSMT
{
    public:
        SimulatorTSMT();
        virtual ~SimulatorTSMT();

        static void PrintExperimental(const TSInput & tsin, const EnjoLib::VecD & data, const EnjoLib::Str & descr, const STDFWD::vector<const EnjoLib::VecD *> & plots);

        static STDFWD::vector<TSRes> GetRetsMT(const STDFWD::vector<SimulatorTS::Inp> input);

    protected:

    private:
};

#endif // SIMULATORTSMT_H
