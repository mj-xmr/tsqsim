#include "EnumStringMapBufferVecType.h"
#include <BufferVecType.h>

EnumStringMapBufferVecType::EnumStringMapBufferVecType()
{
    for (int i = 0; i <= int(BufferVecTypeEnum::BUF_VEC_NONE); ++i)
    {
        BufferVecTypeEnum type = BufferVecTypeEnum(i);
        switch (type) // Generate compiler warnings
        {
            case BufferVecTypeEnum::BUF_VEC_NONE:           Add(type, "None"); break;
            case BufferVecTypeEnum::BUF_VEC_MACD:           Add(type, "MACD"); break;
            case BufferVecTypeEnum::BUF_VEC_BBANDS:         Add(type, "BBands"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_HIST:        Add(type, "Ma Hist"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_RIBBON:      Add(type, "Ma Rib"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_DIFFS:       Add(type, "Ma Diffs"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_SPEED:       Add(type, "Ma Speed"); break;
            
            case BufferVecTypeEnum::BUF_VEC_MA_REG_RIBBON:  Add(type, "MaR Rib"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_REG_DIFFS:   Add(type, "MaR Diffs"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_REG_SPEED:   Add(type, "MaR Speed"); break;
            
            case BufferVecTypeEnum::BUF_VEC_MA_ACOR_RIBBON: Add(type, "MaA Rib"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_ACOR_DIFFS:  Add(type, "MaA Diffs"); break;
            case BufferVecTypeEnum::BUF_VEC_MA_ACOR_SPEED:  Add(type, "MaA Speed"); break;
            
            case BufferVecTypeEnum::BUF_VEC_MAMA_FAMA:      Add(type, "MaFama"); break;
            
            case BufferVecTypeEnum::BUF_VEC_STOCH:          Add(type, "Stoch"); break;
            case BufferVecTypeEnum::BUF_VEC_SIN:            Add(type, "Sin"); break;
            case BufferVecTypeEnum::BUF_VEC_EDECOMP:        Add(type, "Edecomp"); break;
            case BufferVecTypeEnum::BUF_VEC_AUTOCORREL:     Add(type, "Acorrel"); break;
            case BufferVecTypeEnum::BUF_VEC_ACOR_DIFFS:     Add(type, "Acor Diffs"); break;
            case BufferVecTypeEnum::BUF_VEC_ACOR_SPEED:     Add(type, "Acor Speed"); break;
            
            case BufferVecTypeEnum::BUF_VEC_ROC:            Add(type, "ROC"); break;
            case BufferVecTypeEnum::BUF_VEC_GARCH:          Add(type, "Garch"); break;
            case BufferVecTypeEnum::BUF_VEC_ZZ_DIFFS:       Add(type, "ZZDiffs"); break;
            case BufferVecTypeEnum::BUF_VEC_STATION:        Add(type, "Station"); break;

            //case BufferVecTypeEnum::BUF_TEST:                  Add(type, "Test"); break;
        }
    }
}

EnumStringMapBufferVecType::~EnumStringMapBufferVecType()
{
    //dtor
}
