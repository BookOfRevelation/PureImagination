#include "pureconfiguration.h"
#include <QFile>
#include <QDebug>
#include "purecore.h"

QSettings* PureConfiguration::settings;
QString PureConfiguration::bgName;
int PureConfiguration::windowGeometry[4];

PureConfiguration::PureConfiguration()
{

}


void PureConfiguration::loadConf()
{
    QFile f("./conf.ini");
    if( !f.open(QIODevice::ReadWrite))
    {
        qDebug()<<"not found";
    }
    f.close();
    settings = new QSettings("./conf.ini", QSettings::IniFormat);
    bgName = ":/res/bg.png";
    bool result = settings->childGroups().contains("global", Qt::CaseInsensitive);
    if(result)
    {
        bgName = settings->value("global/bgPath").toString();
        PureCore::lastOpenDir = settings->value("global/openDir").toString();
        PureCore::lastTargetDir = settings->value("global/targetDir").toString();

        windowGeometry[0] = settings->value("ui/winW", 1024).toInt();
        windowGeometry[1] = settings->value("ui/winH", 768).toInt();
        windowGeometry[2] = settings->value("ui/winX").toInt();
        windowGeometry[3] = settings->value("ui/winY").toInt();


    }
}

void PureConfiguration::saveConf()
{
    settings->setValue("global/bgPath", bgName);
    settings->setValue("global/openDir", PureCore::lastOpenDir);
    settings->setValue("global/targetDir", PureCore::lastTargetDir);

    settings->setValue("ui/winW", windowGeometry[0]);
    settings->setValue("ui/winH", windowGeometry[1]);
    settings->setValue("ui/winX", windowGeometry[2]);
    settings->setValue("ui/winY", windowGeometry[3]);

    delete settings;

}
