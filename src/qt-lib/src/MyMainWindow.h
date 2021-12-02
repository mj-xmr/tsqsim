#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include "mainwindow.h"
#include "Monster.h"
#include <RegressionPars.h>
#include <State.h>
#include <Template/CorradePointerFwd.h>

//#undef DEBUG

class PlotDataBase;
class PlotData;
class ConfigSym;
class ConfigTF2;
class ConfigQTPlot;
class LabelQT;
class IStrategy;
class ISymbol;
class ISimulator;
class ISimulatorStd;
class SimulatorBet;
class SymbolFactoryAbstract;
class MainTester;

class MyMainWindow : public MainWindow
{
    public:
        MyMainWindow(QWidget *parent = 0);
        virtual ~MyMainWindow();

        void Reload(const Monster & monst, int mode = 0, int relPeriod = 0, int relShift = 0, int relSymbol = 0);
        void setupBaustelle(QCustomPlot * customPlot, const IPeriod & period, const IStrategy & strat, const PlotDataBase & d);
        void setupVisuals(QCustomPlot * customPlot, const IPeriod & period, const IStrategy & strat, const PlotDataBase & d, double binSize);
        void setupVisualsBig(QCustomPlot * p, const IPeriod & period, const IStrategy & strat, const PlotData & d);

        void SetLabelStart(int i);
        void SetLabelEnd(int i);
        void NewLabelStrat(bool bullish);
        void DeleteLabelStrat();
        void SaveLabel();
        void UpdateCursor(double x, double y);
        void UpdateTrendLine(double x, double y, bool start);
        void RegressionStart(int i);
        void RegressionEnd(int i);
        void RegressionMove(int i);
        void RegressionEndOpti(int i);
        void RegressionStationarityPython();
        void RegressionDegreeUp();
        void RegressionDegreeDown();
        void RegressionPlot(bool opti);
        void DumpPeriod();
        void NovelityPython(int i);
        void Bet(int i);
        void StartTimer(int speed);
        void StopTimer();
        QCustomPlot * GetQCP();
        const PlotDataBase & GetData() const;
        const IPeriod & GetPeriod() const;
        const ISymbol & GetSymbol() const;
        const IStrategy & GetStrategy() const;
        void SetDark(bool dark) { m_dark = dark; }
        int CalcIdxMon(int i) const;


        unsigned m_i = 0;
        bool m_dirRight = true;
        double m_x;
        double m_y;
        unsigned m_iMouse = 0;

        Monster m_mons;


        bool m_training = false;
        unsigned m_iTraining = 0;
        bool m_trainingShow = false;
        std::vector<State> m_sigStatesTraining;
        std::vector<State> m_trainingStatesAccepted;

        QCPFinancial * m_candlesticks = nullptr;
        QCPGraph * m_slBull = nullptr;
        QCPGraph * m_slBear = nullptr;
        QCPItemText * m_txtPrice = nullptr;

    protected:
        virtual void mousePress(QMouseEvent *event);
        virtual void mouseRelease(QMouseEvent *event);
        virtual void mouseMove(QMouseEvent *event);
        //bool event(QEvent * event);
        void keyPressEvent(QKeyEvent *event);
        void timerEvent(QTimerEvent *event);
    private:
        QCPAxisRect * SetupTechs(QCustomPlot * p, const IStrategy & strat, const PlotDataBase & d);
        void HandleScreenshot(ConfigSym * pconf);
        int HandleRelativeParUpdate(int relPar, int * relMember);
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFile() const;

        std::vector<QCPAbstractItem *> m_regressLineUser;
        QCPAxisRect * m_techRect = nullptr;
        QCPGraph * m_techLineCursor = nullptr;
        QCPItemLine *m_hCursor = nullptr, *m_vCursor = nullptr;
        QCPItemLine * m_trendLine = nullptr;
        //const PlotDataBase * m_d = nullptr;

        //EnjoLib::Str m_screenShotOutDir;
        //EnjoLib::Str m_screenShotSymbol;
        //EnjoLib::Str m_screenShotPeriod;
        //EnjoLib::Str m_dataInputFileName;



        int timerId = 0;
        int m_relPeriod = 0;
        int m_relShift = 0;
        int m_relSymbol = 0;
        bool m_dark = false;
};

#endif // MYMAINWINDOW_H
