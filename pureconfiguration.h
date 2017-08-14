#ifndef PURECONFIGURATION_H
#define PURECONFIGURATION_H

#include <QSettings>

class PureConfiguration
{
public:
    PureConfiguration();

    static void loadConf();
    static void saveConf();


//SETTINGS
    static QString bgName;
    static int windowGeometry[4];

private:

    static QSettings* settings;


};

#endif // PURECONFIGURATION_H
