#ifndef ENUMSTRINGMAPSTRAT_H
#define ENUMSTRINGMAPSTRAT_H

#include <Util/EnumStringMap.hpp>


class EnumStringMapStrat : public EnjoLib::EnumStringMap
{
    public:
        EnumStringMapStrat();
        virtual ~EnumStringMapStrat();

    protected:

    private:
        void AddPriv(int istrat);
};

#endif // ENUMSTRINGMAPSTRAT_H
