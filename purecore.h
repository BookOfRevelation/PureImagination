#ifndef PURECORE_H
#define PURECORE_H

#include <QString>
#include <QWidget>
#include "puredata.h"

class PureCore
{
public:

    enum PureType
    {
        NoType, Image, XYZ, Wave, Text
    };

    enum PureNature
    {
        Loader, Filter, Transformater, Saver
    };
    PureCore();

    static void initRNG();

    static int getRandom(int min, int max);
    static QWidget* getEmptyWidget(const QString& lbl);

    static QString lastTargetDir;
    static QString lastOpenDir;

    static PureType currentOutput;

    static PureData* currentData;

    static QString TypeToStr(PureType n);

    static QImage applyEffectToImage(QImage src, int blur, int extent = 0);
};

#endif // PURECORE_H
