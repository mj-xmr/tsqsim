#include "IMainTester.h"


IMainTester::IMainTester()
{
    //ctor
}

IMainTester::~IMainTester()
{
    //dtor
}


#include "MainTester.h"
#include <Template/CorradePointer.h>
CorPtr<IMainTester> IMainTester::Create(const SymbolFactoryAbstract & symFact, 
                                        const ConfigTF2 * m_confTF2, const ConfigSym * confSym, bool verbose)
{
    return CorPtr<IMainTester>(new MainTester(symFact, m_confTF2, confSym, verbose));
}