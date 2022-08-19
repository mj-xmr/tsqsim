#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "RegressionPars.h"
#include <Util/Str.hpp>
#include <Template/SharedPtr.hpp>
#include <3rdParty/stdfwd.hh>

class ConfigTF2;
class ConfigSym;
class PlotDataBase;
class PlotData;
class ConfigQTPlot;
class LabelQT;
class IStrategy;
class ISymbol;
class IPeriod;
class ISimulator;
class ISimulatorStd;
class SimulatorBet;
class ISimulatorBet;
class SymbolFactoryAbstract;
class StrategyFactoryAbstract;
class SimulatorFactoryAbstract;
class StrategyType;
class IMainTester;
class TxtSimulatorBase;
class TxtSmallBase;

class Monster
{
    public:
        Monster();
        Monster(const EnjoLib::Str & screenShotOutDir, const EnjoLib::Str & screenShotSymbol,
                const EnjoLib::Str & screenShotPeriod, const EnjoLib::Str & dataInputFileName);
        virtual ~Monster();

        /// TODO: Code smell
        void SetFactories(  SymbolFactoryAbstract * pSymFact,
                            StrategyFactoryAbstract * pStratFact,
                            SimulatorFactoryAbstract  * pSimFact
                                                          );

        void SetFactories(const Monster & mons);

        virtual void InitVirt();


        void Reload(const EnjoLib::Str & symName, const EnjoLib::Str & periodName, const StrategyType & stratType,
                    int mode = 0, int relPeriod = 0, int relShift = 0, int relSymbol = 0);
        bool IsValid() const;
        static EnjoLib::Str FindNextPeriodIndex(const SymbolFactoryAbstract & symFact, const ConfigTF2 & confTF2, const ConfigSym * pconf, EnjoLib::Str symName, EnjoLib::Str periodName, int relPeriod);

        EnjoLib::Str m_screenShotOutDir;
        EnjoLib::Str m_screenShotSymbol;
        EnjoLib::Str m_screenShotPeriod;
        EnjoLib::Str m_dataInputFileName;

        EnjoLib::Str m_periodName;

        EnjoLib::SharedPtr<ISymbol> m_symbol;
        EnjoLib::SharedPtr<PlotDataBase> m_d;
        EnjoLib::SharedPtr<TxtSimulatorBase> m_simulTxt;
        EnjoLib::SharedPtr<TxtSmallBase> m_smallTxt;
        EnjoLib::SharedPtr<IStrategy> m_strategy;
        EnjoLib::SharedPtr<LabelQT> m_labelQT;

        SymbolFactoryAbstract * m_symFact = nullptr;
        StrategyFactoryAbstract * m_stratFact = nullptr;
        SimulatorFactoryAbstract * m_simFact = nullptr;

        EnjoLib::SharedPtr<IMainTester> m_mainTester;
        EnjoLib::SharedPtr<ISimulator> m_simulatorGeneric;
        //EnjoLib::SharedPtr<ISimulatorStd> m_simulator;
        //EnjoLib::SharedPtr<ISimulatorBet> m_simulatorBet;

        double m_percentBars = 100;
        long int m_barNum = 0;
        RegressionPars reg;
        bool m_training = false;

    protected:

    private:
        void InitBufs(const IPeriod & per) const;

        bool m_isValid = false;

};

#endif // MONSTER_HPP
