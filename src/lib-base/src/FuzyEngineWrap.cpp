#include "FuzyEngineWrap.h"
#include <Util/CoutBuf.hpp>

FuzyEngineWrap::FuzyEngineWrap(std::vector<LinguisticVariable *> inVars, LinguisticVariable & outVar, const std::vector <std::string> & rules)
: m_outVar(outVar)
{
    for (auto inVar : inVars)
        m_fuzzyEngine.regist(inVar);
    m_fuzzyEngine.regist(&outVar);

    m_fuzzyBlockOfRules = new FuzzyBlockOfRules(rules);
    m_fuzzyEngine.regist(m_fuzzyBlockOfRules);
    m_fuzzyBlockOfRules->parseBlock();
}

FuzyEngineWrap::~FuzyEngineWrap()
{
    delete m_fuzzyBlockOfRules;
}

float FuzyEngineWrap::GetOutput()
{
    Evaluate();
    float score = Defuzzify();
    Reset();
    return score;
}

void FuzyEngineWrap::Evaluate()
{
    m_fuzzyBlockOfRules->evaluateBlock();
}

float FuzyEngineWrap::Defuzzify()
{
    float ret = 0;
    try
    {
        ret = m_outVar.defuzzify();
    }
    catch (NoRulesFiredException & e)
    {
        LOGL << "Exception 2: " << e.what() << EnjoLib::Nl;
    }
    return ret;
}

void FuzyEngineWrap::Reset()
{
    m_fuzzyEngine.reset();
}
