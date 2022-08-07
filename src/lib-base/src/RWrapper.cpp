#include "RWrapper.h"

#include <Util/Except.hpp>
#include <Util/FileUtils.hpp>

#ifdef USE_R
#include <Rinternals.h>
#include <Rembedded.h>
#endif //USE_R

#include <cstring>
#include <STD/VectorCpp.hpp>

RWrapper::RWrapper()
{
}

RWrapper::~RWrapper()
{
}

/**
 * Wrapper for R function predict, defined in func.R.
 */
EnjoLib::VecD RWrapper::R_predictVec(const EnjoLib::VecD & vecd)
{
    const std::vector<double> vec = vecd.ToVecDouble();
    EnjoLib::VecD retVec;   
#ifdef USE_R
    const double * a = vec.data();
    const int alen = vec.size();
    const char * functionName = "predict";

    // Allocate an R vector and copy the C array into it.
    SEXP arg;
    PROTECT(arg = allocVector(REALSXP, alen));
    std::memcpy(REAL(arg), a, alen * sizeof(double));

    // Setup a call to the R function
    SEXP add1_call;
    PROTECT(add1_call = lang2(install(functionName), arg));

    // Execute the function
    int errorOccurred;
    SEXP ret = R_tryEval(add1_call, R_GlobalEnv, &errorOccurred);

    if (!errorOccurred)
    {
        printf("R returned: ");
        double *val = REAL(ret);
        for (int i = 0; i < LENGTH(ret); i++)
        {
            printf("%0.1f, ", val[i]);
            retVec.Add(val[i]);
        }
            
        printf("\n");
    }
    else
    {
        printf("Error occurred calling R\n");
    }
    
    UNPROTECT(2);
#endif //USE_R
    return retVec;
}

/**
 * Invokes the command source(scriptPath).
 */
void RWrapper::source(const EnjoLib::Str & scriptPath)
{
    if (not EnjoLib::FileUtils().FileExists(scriptPath))
    {
        throw EnjoLib::ExceptInvalidArg("RWrapper::source(): File doesn't exist: " + scriptPath);
    }
#ifdef USE_R
    SEXP e;

    PROTECT(e = lang2(install("source"), mkString(scriptPath.c_str())));
    R_tryEval(e, R_GlobalEnv, NULL);
    UNPROTECT(1);
#endif //USE_R
}
