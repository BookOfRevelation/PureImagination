#ifndef XYZTOIMG_H
#define XYZTOIMG_H

#include <QImage>
#include "puretransformater.h"
#include "pureimage.h"
#include "purexyz.h"

class XYZToImg : public PureTransformater
{
public:
    XYZToImg(const QString& n);

    bool init();
    void process();
    PureEffect* clone()
    {
        XYZToImg* e = new XYZToImg(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p)
    {
        Q_UNUSED(p);
    }

    QVector<QVariant> getParameters() const
    {
        QVector<QVariant> r;
        r.clear();
        return r;
    }

    PureCore::PureType getInputType() { return PureCore::XYZ ;}
    PureCore::PureType getOutputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "PointCloud to Img",
                    "Transforme une image en \n"
                    "nuage de points 3D."
                    );
    }

};

#endif // XYZTOIMG_H
