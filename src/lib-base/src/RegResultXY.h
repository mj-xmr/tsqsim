#ifndef REGRESULTXY_H
#define REGRESULTXY_H

//#include <Statistical/RegressionAbstract.hpp>
#include "RegressionPoints.h"
#include "RegressionPars.h"
#include "RegressionRes.h"
#include "XY.h"
#include <Util/Pimpl.hpp>
#include <Template/ArrayFwd.hpp>

class RegResultXY
{
    public:
        RegResultXY(const RegressionPars & pars = RegressionPars());
        virtual ~RegResultXY();

        double GetDelta() const;
        double GetDelta2RMS() const;
        double GetLen2RMS() const;
        float GetSumZZ() const;
        bool IsValid() const;
        void EraseAllButLast();
        void Reserve(int memSize);
        void Shrink2Fit();
        static XY FindXYInRegResultXY(const EnjoLib::Array<XY> & vxy, int sti);

        /*
        std::vector<XY> regLine;
        std::vector<XY> regOver;
        std::vector<XY> regUndr;
        std::vector<XY> regOverBody;
        std::vector<XY> regUndrBody;
        std::vector<XY> regOverUnderAvg;
        std::vector<XYDir> zzz;
        */
        size_t size() const;
        EnjoLib::Array<XY> regLine() const;
        EnjoLib::Array<XY> regOver() const;
        EnjoLib::Array<XY> regUndr() const;
        EnjoLib::Array<XY> regOverBody() const;
        EnjoLib::Array<XY> regUndrBody() const;
        EnjoLib::Array<XY> regOverUnderAvg() const;
        const STDFWD::vector<XYDir> & zzz() const;

        const float & regLineBackY() const;
        const float & regOverBackY() const;
        const float & regUndrBackY() const;
        const float & regOverBodyBackY() const;
        const float & regUndrBodyBackY() const;
        const float & regOverUnderAvgBackY() const;
        const XYDir & zzzBack() const;

        const XY & regLineBack() const;
        const XY & regOverBack() const;
        const XY & regUndrBack() const;
        const XY & regOverBodyBack() const;
        const XY & regUndrBodyBack() const;
        const XY & regOverUnderAvgBack() const;

        STDFWD::vector<XY> & regLine();
        STDFWD::vector<XY> & regOver();
        STDFWD::vector<XY> & regUndr();
        STDFWD::vector<XY> & regOverBody();
        STDFWD::vector<XY> & regUndrBody();
        STDFWD::vector<XY> & regOverUnderAvg();
        STDFWD::vector<XYDir> & zzz();

        PIMPL_CPY

    public:
        double rmsMinMax = 0;
        double pointsOver = 0;
        double pointsUndr = 0;
        int ageLatestCIUpper = 0;
        int ageLatestCILower = 0;
        RegressionRes regRes;
        RegressionPoints regPts;
        RegressionPars regPar;


    protected:

    private:

};

#endif // REGRESULTXY_H
