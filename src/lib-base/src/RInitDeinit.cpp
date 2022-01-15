#include "RInitDeinit.h"

#ifdef USE_R
#include <Rinternals.h>
#include <Rembedded.h>
#endif //USE_R

RInitDeinit::RInitDeinit()
{
#ifdef USE_R
    int r_argc = 2;
    char *r_argv[] = { "R", "--silent" };
    Rf_initEmbeddedR(r_argc, r_argv);
#endif //USE_R
}

RInitDeinit::~RInitDeinit()
{
#ifdef USE_R
    Rf_endEmbeddedR(0);
#endif //USE_R
}
