#ifndef IMAGETOXYZ_H
#define IMAGETOXYZ_H

#include <QImage>
#include "puretransformater.h"
class ImageToXYZ  : public PureTransformater
{
public:
    ImageToXYZ();
    bool init();

    void process();


    float splitFactor;
    QVector<QImage> baseImages;

    QString targetFile;

    PureCore::PureType getOutputType() { return PureCore::XYZ ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}



};

#endif // IMAGETOXYZ_H
