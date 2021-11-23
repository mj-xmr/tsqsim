#include "DTWWrap.h"
#include "IDataProvider.h"
//#include "TradeUtil.h"
//#include "ConfigDirs.h"
//#include "ConfigMan.h"
//#include "ConfigML.h"
#include "Err.h"
#include "DTWIDistComp.h"
#include "State.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "IModel.h"

//#include <EnjoLibBoost/Filesystem.hpp>
//#include <Util/Tokenizer.hpp>
//#include <Util/CharManipulations.hpp>
//#include <Util/Ifstream.hpp>
//#include <Util/FileUtils.hpp>
//#include <Template/LoopThreadedTpl.hpp>
#include <Math/GeneralMath.hpp>

#include <Statistical/Assertions.hpp>
#include <Statistical/MeanWeighted.hpp>
#include <Template/CorradePointer.h>
#include <Template/Array.hpp>

#include <Util/CoutBuf.hpp>
//#include <Util/Except.hpp>
//#include <functional>
#include <STD/VectorCpp.hpp>
#include <STD/Map.hpp>

using namespace std;
using namespace EnjoLib;

DTWWrap::~DTWWrap(){}
DTWWrap::DTWWrap(){}

VecD GetMinDistBase(const DTWIDistComp & comp, const EnjoLib::VecD & obsNew, const IModel & mod, const IBufferCandles & bufCan, const EnjoLib::Array<LabelML> & knnLabs, const Mask & mask, DateInt istate)
{
    static int NUM_CLOSEST = 20;
    static float MAX_DIST_MUL = 10;
    static double LOG_DECAY = 3;  // Greater numbers - slower decay
    
    const GeneralMath gmat;
    MaxMinFindF mmf;
    //EnjoLib::Osstream ossIndiv;

    struct IdxStateDiff
    {
        int idx;
        int diffSts;
    };
    //LoopThreadedTpl<DataDist, double> loop(knnLabs.size(), &ConvDist);
    //vector<DataDist> datas;
    //cout << "knn size = " << knnLabs.size() << ", tol = " << tol << endl;
    map<double, IdxStateDiff> distances;
    for (int i = 0; i < int(knnLabs.size()); ++i)
    {
        int diffStsGlob = 0;
        const LabelML & labEx  = knnLabs.at(i);
        const DateInt labistate = labEx.GetDate();
        if (labistate == istate)
        {
            // Same label
            continue;
        }
        /// bufCan  can be used to calculate time difference
        //if (bufCan.HasNearestCandle(labistate)) // CPU hogs
        if (bufCan.HasCandle(labistate)) // CPU hogs
        {
            //cout << "Has candle labistate " << labistate << ", istate = " << istate << endl;
            const int stiLab = bufCan.GetIndexSti(labistate);
            //const int stiLab = bufCan.GetIndexSti(bufCan.GetNearestCandle(labistate).GetDate());
            const int stiObs = bufCan.GetIndexSti(istate);
            if (stiLab < stiObs)
            {
                //cout << "labistate " << labistate << ", istate = " << istate << endl;
                continue;
            }
            const int minDist = mod.MIN_LEN() + 1;
            const int diffSts = abs(stiLab - stiObs);
            diffStsGlob = diffSts;
            if (diffSts < minDist)
            {
                //cout << "labistate " << labistate << ", istate = " << istate << endl;
                continue;
            }
            //else
            {
                //cout << "Good! labistate " << labistate << ", istate = " << istate << endl;
            }
        }
        else
        {
            //cout << "bufCan.Len() = " << bufCan.Len() << endl;
            LOGL << "No candle labistate " << labistate << ", istate = " << istate << ", max = " << bufCan[0].GetDate() << ", min = " << bufCan[bufCan.Len() - 1].GetDate() << EnjoLib::Nl;
            continue;
        }
        //const int stiLab = bufCan.GetIndexSti(labistate);
        //const int stiObs = bufCan.GetIndexSti(istate);
        //if (stiLab > stiObs)
        {
            //cout << "labistate " << labistate << ", istate = " << istate << endl;
            //continue;
        }
        //else
        {
            //cout << "Good! labistate " << labistate << ", istate = " << istate << endl;
        }
        
        const VecD & obsVec = labEx.GetFlatObserv4Mask(mask);
        Assertions::NonEmpty  (mask, "DTWWrap::GetMinDist(): empty mask");
        Assertions::NonEmpty  (obsVec, "DTWWrap::GetMinDist(): empty matrix");
        //Assertions::SizesEqual(obsVec, obsNew, "DTWWrap::GetMinDist(): diff size");
        //cout << "Size labEx = " << labEx.observs.Flatten().size() << ", size lab Obs = " << obsNew.size() << endl;

        //loop.AddInput(i, DataDist(comp, labEx, mask));
        //datas.push_back(DataDist(comp, labEx, mask));

        const double newbest = comp.Compare(obsVec);
        if (mmf.UpdateMin(newbest, i))
        {
            //cout << "Target = " << labEx.target << endl;
            //const Err error = GetError(lab, knnLabs.at(mmf.GetMinIdx()));
            //ossIndiv << " we found a new nearest neighbor, distance (L1 norm) = " << newbest << ". profit = " << labEx.targets.at(0) <<  '\n'; // ", tgt diff = " << error.absol() << "\n";
            //resultsKnn << mmf.GetMin() << " " << error.absol() << "\n";
            //dists.push_back(mmf.GetMin()); errors.push_back(error.absol());
            //cout << ossIndiv;
            IdxStateDiff isd;
            isd.idx = i;
            isd.diffSts = diffStsGlob;
            distances[mmf.GetMin()] = isd;
         }

    }
    /*
    loop.AddInputVector(datas);
    int i = 0;
    for (const double newbest : loop.GetOutputVector())
    {
        if (mmf.UpdateMin(newbest, i++))
        {
        }
    }
    */
    //return std::vector<EnjoLib::MaxMinFindF>{mmf};
    
    const double bestDist = mmf.GetMin();
    // Doesn't work well:
    VecD ret;
    //Assertions::IsTrue(minIdx >= 0, "DTWWrap::GetMinDist(): empty distances");
    int i = 0;
    double weightSum = 0;
    for (auto it = distances.begin(); it != distances.end() && i < NUM_CLOSEST; ++it, ++i)
    { 
        const double dist   = it->first;// / bestDist; // makes no difference
        const int minIdxLoc = it->second.idx;
        const int ageDiff = it->second.diffSts;
        //const int ageDiff = 1;
       
        Assertions::IsTrue(dist > 0, "DTWWrap::GetMinDist(): div by zero");
        //cout << "Dist = " << dist << endl;
        
        const double distRelative = dist / bestDist;
        if (distRelative > MAX_DIST_MUL)
        {
            break;
        }
        
        const LabelML & found = knnLabs.at(minIdxLoc);
        const double weightAge = gmat.Exp(-gmat.Log(ageDiff) / LOG_DECAY);
        const double weightDist = 1 / dist;
        const double weight = weightAge + weightDist;
        //const double weight = 1 / dist / dist;
        weightSum += weight;
        VecD tgtWeighted = found.targets * weight;
        
        if (ret.empty())
            ret = tgtWeighted;
        else
            ret += tgtWeighted; // sum
        
        //cout << i << " dist = " << dist << " weight = " << weight << endl;
    }
    //cout << endl;
    //Assertions::IsTrue(i > 0, "DTWWrap::GetMinDist(): div by zero");
    ret /= weightSum; // Average

    return ret;
}

EnjoLib::VecD DTWWrap::GetMinDist(int i, const DateInt & date, const DTWDistType & type, const EnjoLib::VecD & obsNew, const IModel & mod, 
                                const IBufferCandles & bufCan, const EnjoLib::Array<LabelML> & knnLabs, const Mask & mask) const
{
    const CorPtr<DTWIDistComp> distComp = DTWIDistComp::Create(type, obsNew);
    return GetMinDistBase(*distComp, obsNew, mod, bufCan, knnLabs, mask, date);
}

Err DTWWrap::GetError(const LabelML & laba, const VecD & targets) const
{
    return Err(laba, targets);
}

/*
struct DataDist
{
    DataDist(const IDistanceComparator & comp, const LabelML & labEx, const Mask & mask)
    : comp(comp)
    , labEx(labEx)
    , mask(mask)
    {

    }

    const IDistanceComparator & comp;
    const LabelML & labEx;
    const Mask & mask;
};

static double ConvDist(const DataDist & dataDist)
{
    const VecD & obsVec = dataDist.labEx.GetFlatObserv4Mask(dataDist.mask);
    Assertions::NonEmpty  (obsVec, "DTWWrap::GetMinDist(): empty matrix");
    //Assertions::SizesEqual(obsVec, obsNew, "DTWWrap::GetMinDist(): diff size");
    //cout << "Size labEx = " << labEx.observs.Flatten().size() << ", size lab Obs = " << obsNew.size() << endl;
    double newbest = dataDist.comp.Compare(obsVec);
    return newbest;
}
*/
