#include "EnumStringMapPlotType.h"
#include <Util/Str.hpp>
#include <PlotType.h>

EnumStringMapPlotType::EnumStringMapPlotType()
{
    PlotType type = PlotType::PLOT_NONE;
    switch (type) // Generate compiler warnings
    {
        case PlotType::PLOT_NONE:
        case PlotType::PLOT_LABELS:
        case PlotType::PLOT_TRAINER:
        case PlotType::PLOT_SIGNALS:
        case PlotType::PLOT_SL_AUSW:
        break;
    }
    Add(PlotType::PLOT_NONE, "None");
    Add(PlotType::PLOT_LABELS, "Labs");
    Add(PlotType::PLOT_TRAINER, "Train");
    Add(PlotType::PLOT_SIGNALS, "Sigs");
    Add(PlotType::PLOT_SL_AUSW, "SL ausw");
}

EnumStringMapPlotType::~EnumStringMapPlotType()
{
}
