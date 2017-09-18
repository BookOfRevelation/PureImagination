#ifndef IMAGETOXYZ_H
#define IMAGETOXYZ_H

#include <QImage>
#include "puretransformater.h"
class ImageToXYZ  : public PureTransformater
{
public:
    ImageToXYZ(const QString &n);

    bool init();
    void process();

    PureEffect* clone()
    {
        ImageToXYZ* e = new ImageToXYZ(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    float splitFactor;

    PureCore::PureType getOutputType() { return PureCore::XYZ ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Img to PointCloud",
                    "Transforme une image en \n"
                    "nuage de points 3D."
                    );
    }



};

#endif // IMAGETOXYZ_H
