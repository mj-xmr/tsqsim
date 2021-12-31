#include "TSXformDataMan.h"

TSXformDataMan::TSXformDataMan()
{
    //ctor
}

TSXformDataMan::~TSXformDataMan()
{
    //dtor
}

void TSXformDataMan::Add(const TSRes & tsres)
{
    converted.Add(tsres.val);
    convertedLost.Add(tsres.lost);
}

int TSXformDataMan::Len() const
{
    return convertedLost.size();
}
