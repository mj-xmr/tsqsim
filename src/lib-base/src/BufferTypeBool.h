#ifndef BUFFERTYPEBOOL_H_INCLUDED
#define BUFFERTYPEBOOL_H_INCLUDED

enum BufferTypeBoolEnum
{
    BUF_BOOL_ZZ_HI,
    BUF_BOOL_ZZ_LO,
    BUF_BOOL_FRACT_UP,
    BUF_BOOL_FRACT_DOWN,
    BUF_BOOL_NONE,
};

/// Saves compilation time on new enum members
class BufferTypeBool
{
public:
    BufferTypeBool(BufferTypeBoolEnum type) {this->type = type;}
    BufferTypeBoolEnum type;
    BufferTypeBoolEnum GetType() const
    {
        return type;
    }
};

#endif // BUFFERTYPEBOOL_H_INCLUDED
