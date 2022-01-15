#include "RInitDeinit.h"

#ifdef USE_R
#include <Rinternals.h>
#include <Rembedded.h>
#endif //USE_R

RInitDeinit::RInitDeinit()
{
#ifdef USE_R
    const int r_argc = 3;
    char *r_argv[] = { "R", "--silent", "--vanilla" };
    Rf_initEmbeddedR(r_argc, r_argv);
#endif //USE_R
}

RInitDeinit::~RInitDeinit()
{
#ifdef USE_R
    Rf_endEmbeddedR(0);
#endif //USE_R
}
