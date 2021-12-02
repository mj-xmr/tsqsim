#include "LabelsUtil.h"
#include "ConfigDirs.h"
#include "IStrategy.h"

#include <Util/Str.hpp>


LabelsUtil::LabelsUtil(){}
LabelsUtil::~LabelsUtil(){}

EnjoLib::Str LabelsUtil::GetLabelSignalPath(const IStrategy & strat)
{
    return GetLabelSignalPath(strat.GetName());
}

EnjoLib::Str LabelsUtil::GetLabelSignalDir(const IStrategy & strat)
{
    return GetLabelSignalDir(strat.GetName());
}

EnjoLib::Str LabelsUtil::GetLabelSignalDir(const EnjoLib::Str & stratName)
{
    return GetLabelDir(ConfigDirs().DIR_LABELS_SIGNAL, stratName);
}
EnjoLib::Str LabelsUtil::GetLabelSignalPath(const EnjoLib::Str & stratName)
{
    return GetLabelPath(ConfigDirs().DIR_LABELS_SIGNAL, stratName);
}

EnjoLib::Str LabelsUtil::GetLabelRangeDir(const IStrategy & strat)
{
    return GetLabelRangeDir(strat.GetName());
}
EnjoLib::Str LabelsUtil::GetLabelRangePath(const IStrategy & strat)
{
    return GetLabelRangePath(strat.GetName());
}
EnjoLib::Str LabelsUtil::GetLabelRangeDir(const EnjoLib::Str & stratName)
{
    return GetLabelDir(ConfigDirs().DIR_LABELS_RANGE, stratName);
}
EnjoLib::Str LabelsUtil::GetLabelRangePath(const EnjoLib::Str & stratName)
{
    return GetLabelPath(ConfigDirs().DIR_LABELS_RANGE, stratName);
}

//EnjoLib::Str LabelsUtil::GetLabelId(const IPeriod & period, const LabelSignal & labSig)
//{}


EnjoLib::Str LabelsUtil::GetLabelDir(const EnjoLib::Str & prefixDir, const IStrategy & strat)
{
    return GetLabelDir(prefixDir, strat.GetName());
}
EnjoLib::Str LabelsUtil::GetLabelPath(const EnjoLib::Str & prefixDir, const IStrategy & strat)
{
    return GetLabelPath(prefixDir, strat.GetName());
}
EnjoLib::Str LabelsUtil::GetLabelDir(const EnjoLib::Str & prefixDir, const EnjoLib::Str & stratName)
{
    return prefixDir + "/" + stratName;
}
EnjoLib::Str LabelsUtil::GetLabelPath(const EnjoLib::Str & prefixDir, const EnjoLib::Str & stratName)
{
    return prefixDir + "/" + stratName + "/" + ConfigDirs().FILE_LABELS;
}
