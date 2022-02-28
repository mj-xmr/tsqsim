/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 11.10.14                                             **
**          Version: 1.3.0-beta                                           **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/
#include "pch_qt.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Geom.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <ConfigMan.h>
#include <ConfigQT.h>
#include <ConfigGlob.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //,ui(new Ui::MainWindow)
{
    setupWindow();
}

void MainWindow::setupWindow()
{
    const ConfigQT & confQT = *gcfgMan.cfgQT;
    if (not ui)
    {
        ui = new Ui::MainWindow;
    }
    ui->setupUi(this);

#ifdef DEBUG
    //setGeometry(400, 250, 800, 600);
    setGeometry(Geom::xDebug, 0, Geom::wDebug, Geom::hNorm);
#else
    int y = Geom::y;
    int h = Geom::wideScreen ? Geom::hWide : Geom::hNorm;

    if (confQT.BIG_SCREEN)
        setGeometry(Geom::xBig,   y, Geom::wBig,   h); // 16:9
    else
        setGeometry(Geom::xDebug, y, Geom::wDebug, h); // Debug


#endif
    gcfg.DIRECTION = (Direction)confQT.DIRECTION;
    //gcfg.USE_SPREADS = false;
#ifdef DEBUG
    gcfg.USE_CACHE = false;
#else
    gcfg.USE_CACHE = confQT.USE_CACHE;
#endif // DEBUG
    gcfg.IS_QT = true;

    // for making screenshots of the current demo or all demos (for website screenshots):
    //QTimer::singleShot(1500, this, SLOT(allScreenShots()));
    //QTimer::singleShot(4000, this, SLOT(screenShot()));
    //connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->customPlot, &QCustomPlot::mousePress,   this, &MainWindow::mousePress);
    connect(ui->customPlot, &QCustomPlot::mouseRelease, this, &MainWindow::mouseRelease);
    connect(ui->customPlot, &QCustomPlot::mouseMove,    this, &MainWindow::mouseMove);
}

void MainWindow::setupDemo()
{
    //setupBaustelle(ui->customPlot, period);
    statusBar()->clearMessage();
    currentDemoIndex = 0;
    ui->customPlot->replot();
}

void MainWindow::realtimeDataSlot()
{
    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
        // add data to lines:
        ui->customPlot->graph(0)->addData(key, value0);
        ui->customPlot->graph(1)->addData(key, value1);
        // set data of dots:
        ui->customPlot->graph(2)->clearData();
        ui->customPlot->graph(2)->addData(key, value0);
        ui->customPlot->graph(3)->clearData();
        ui->customPlot->graph(3)->addData(key, value1);
        // remove data of lines that's outside visible range:
        ui->customPlot->graph(0)->removeDataBefore(key-8);
        ui->customPlot->graph(1)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
            , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}

void MainWindow::bracketDataSlot()
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double secs = 0;
#else
    double secs = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

    // update data to make phase move:
    int n = 500;
    double phase = secs*5;
    double k = 3;
    QVector<double> x(n), y(n);
    for (int i=0; i<n; ++i)
    {
        x[i] = i/(double)(n-1)*34 - 17;
        y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
    }
    ui->customPlot->graph()->setData(x, y);

    itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

    ui->customPlot->replot();

    // calculate frames per second:
    double key = secs;
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->count())
            , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
    Q_UNUSED(customPlot)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
    QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#endif
    QString fileName = demoName.toLower()+".png";
    fileName.replace(" ", "");
    pm.save("./screenshots/"+fileName);
    qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
    QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#endif
    QString fileName = demoName.toLower()+".png";
    fileName.replace(" ", "");
    pm.save("./screenshots/"+fileName);

    if (currentDemoIndex < 19)
    {
        if (dataTimer.isActive())
            dataTimer.stop();
        dataTimer.disconnect();
        delete ui->customPlot;
        ui->customPlot = new QCustomPlot(ui->centralWidget);
        ui->verticalLayout->addWidget(ui->customPlot);
//        setupDemo(currentDemoIndex+1);
        // setup delay for demos that need time to develop proper look:
        int delay = 250;
        if (currentDemoIndex == 10) // Next is Realtime data demo
            delay = 12000;
        else if (currentDemoIndex == 15) // Next is Item demo
            delay = 5000;
        QTimer::singleShot(delay, this, SLOT(allScreenShots()));
    }
    else
    {
        qApp->quit();
    }
}







































