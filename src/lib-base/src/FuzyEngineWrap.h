#ifndef FUZYENGINEWRAP_H
#define FUZYENGINEWRAP_H

#include <FuzzyEngine++/FuzzyEngine++.hpp>


#include <3rdParty/stdfwd.hh>

class FuzzyBlockOfRules;
class LinguisticVariable;
class FuzyEngineWrap
{
    public:
        FuzyEngineWrap(std::vector<LinguisticVariable *> inVars, LinguisticVariable & outVar, const std::vector <std::string> & rules);
        virtual ~FuzyEngineWrap();
        float GetOutput();

    protected:
    private:
        float Defuzzify();
        void Reset();
        void Evaluate();


        FuzzyEngine m_fuzzyEngine;
        FuzzyBlockOfRules * m_fuzzyBlockOfRules;
        LinguisticVariable & m_outVar;
};

#endif // FUZYENGINEWRAP_H
