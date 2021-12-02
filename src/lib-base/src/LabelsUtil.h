#ifndef LABELSUTIL_H
#define LABELSUTIL_H

#include <Util/Str.hpp>

class IPeriod;
class IStrategy;

class LabelsUtil
{
    public:
        LabelsUtil();
        virtual ~LabelsUtil();

        static EnjoLib::Str GetLabelSignalDir(const IStrategy & strat);
        static EnjoLib::Str GetLabelSignalPath(const IStrategy & strat);
        static EnjoLib::Str GetLabelSignalDir(const EnjoLib::Str & stratName);
        static EnjoLib::Str GetLabelSignalPath(const EnjoLib::Str & stratName);
        //static EnjoLib::Str GetLabelId(const IPeriod & period, const LabelSignal & labSig);

        static EnjoLib::Str GetLabelRangeDir(const IStrategy & strat);
        static EnjoLib::Str GetLabelRangePath(const IStrategy & strat);
        static EnjoLib::Str GetLabelRangeDir(const EnjoLib::Str & stratName);
        static EnjoLib::Str GetLabelRangePath(const EnjoLib::Str & stratName);

    protected:

    private:
        static EnjoLib::Str GetLabelDir(const EnjoLib::Str & prefixDir, const IStrategy & strat);
        static EnjoLib::Str GetLabelPath(const EnjoLib::Str & prefixDir, const IStrategy & strat);
        static EnjoLib::Str GetLabelDir(const EnjoLib::Str & prefixDir, const EnjoLib::Str & stratName);
        static EnjoLib::Str GetLabelPath(const EnjoLib::Str & prefixDir, const EnjoLib::Str & stratName);
};

#endif // LABELSUTIL_H
