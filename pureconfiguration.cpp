#include "pureconfiguration.h"
#include <QFile>
#include <QDebug>

QSettings* PureConfiguration::settings;
QString PureConfiguration::bgName;

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

    }
}

void PureConfiguration::saveConf()
{
    settings->setValue("global/bgPath", bgName);

    delete settings;

}
