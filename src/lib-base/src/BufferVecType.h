#ifndef BUFFERVECTYPE_H
#define BUFFERVECTYPE_H

#include <Util/EnumClassWrapper.hpp>

enum BufferVecTypeEnum
{
    BUF_VEC_SIN,
    BUF_VEC_EDECOMP,
    BUF_VEC_MACD,
    BUF_VEC_STOCH,
    BUF_VEC_MA_RIBBON,
    BUF_VEC_MA_DIFFS,
    BUF_VEC_MA_SPEED,
    BUF_VEC_MA_REG_RIBBON,
    BUF_VEC_MA_REG_DIFFS,
    BUF_VEC_MA_REG_SPEED,
    BUF_VEC_MA_ACOR_RIBBON,
    BUF_VEC_MA_ACOR_DIFFS,
    BUF_VEC_MA_ACOR_SPEED,
    BUF_VEC_BBANDS,
    BUF_VEC_MA_HIST,
    BUF_VEC_MAMA_FAMA,
    BUF_VEC_AUTOCORREL,
    BUF_VEC_ACOR_DIFFS,
    BUF_VEC_ACOR_SPEED,
    BUF_VEC_ROC,
    BUF_VEC_GARCH,
    BUF_VEC_ZZ_DIFFS,
    BUF_VEC_STATION,
    BUF_VEC_STATION_PRED,

    BUF_VEC_NONE
};

/// Saves compilation time on new enum members
class BufferVecType : public EnjoLib::EnumClassWrapper<BufferVecTypeEnum>
{
public:
    using EnumClassWrapper::EnumClassWrapper; // Constructor inheritance
};

#endif // BUFFERVECTYPE_H
