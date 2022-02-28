#ifndef UTILBARE_H
#define UTILBARE_H

#include <Util/Except.hpp>

class UtilBare
{
    public:
        UtilBare();
        virtual ~UtilBare();


        static void HandleException(std::exception & ex);

    protected:

    private:
};

#endif // UTILBARE_H
