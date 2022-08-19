#ifndef TICKSFORMATGUESSER_H
#define TICKSFORMATGUESSER_H

#include "TicksFormat.h"
#include <Util/StrFwd.hpp>
#include "typesStr.h"

class TicksFormatGuesser
{
    public:
        TicksFormatGuesser();
        virtual ~TicksFormatGuesser();

        TicksFormat Run(const VecStr & lines) const;
        TicksFormat Run(const EnjoLib::Str & line, const char delim) const;

    protected:


    private:
};

#endif // TICKSFORMATGUESSER_H
