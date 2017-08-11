#ifndef TANGLEFUSIONEFFECT_H
#define TANGLEFUSIONEFFECT_H

#include <QString>
#include <QPair>
#include <QImage>
#include "purefilter.h"

class TangleFusionEffect : public PureFilter
{
public:
    TangleFusionEffect(const QString &n);
    bool init();

    void process();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

private:

    QString fileName;
    QVector<QImage> baseImages;

};
#endif // TANGLEFUSIONEFFECT_H
