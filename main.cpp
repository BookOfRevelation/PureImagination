#include "mainwindow.h"
#include <QApplication>

#include <stdio.h>
#include <QDebug>
#include <QSound>
#include <QSplashScreen>
#include "purecore.h"
#include "roidialog.h"
#include <iostream>
#include "pureconfiguration.h"



int main(int argc, char *argv[])
{

    PureCore::initRNG();
    PureConfiguration::loadConf();


    QVector<QString> rde;
    rde.push_back("");

    rde.push_back("bitcrush");
    rde.push_back("downsampling");
    rde.push_back("retrigger");
    rde.push_back("ghost");
    rde.push_back("old");

    QApplication a(argc, argv);

    QString rdstr = rde.at(PureCore::getRandom(0, rde.size() -1));
    QSplashScreen ss(QPixmap(QString(":res/pisplash%1.jpg").arg(rdstr)));
    ss.show();
    a.processEvents();


    QSound ms(QString(":res/jinggle%1.wav").arg(rdstr));
    ms.play();


    MainWindow w;
    w.show();
    ss.finish(&w);


    return a.exec();

}
