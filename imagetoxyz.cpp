#include "imagetoxyz.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include <QDir>
#include <QtMath>

#include "pureimage.h"
#include "purexyz.h"
ImageToXYZ::ImageToXYZ(const QString &n)
    : PureTransformater(n),splitFactor(1.05)
{

}


bool ImageToXYZ::init()
{
    return true;
}


void ImageToXYZ::process()
{
    PureImage* img = static_cast<PureImage*>(PureCore::currentData);
    PureXYZ* xyz = new PureXYZ;
    QImage& base = img->getImage(0);
    for(int i = 0 ; i < base.width(); ++i)
    {
        for(int j = 0 ; j < base.height() ; ++j)
        {
            QColor pixelColor = base.pixelColor(i,j);

            xyz->addPoint(i, j, qPow(pixelColor.red()+pixelColor.green()+pixelColor.blue(),splitFactor) );
        }

    }

    delete img;

    PureCore::currentData = xyz;


}

QVector<QVariant> ImageToXYZ::getParameters() const
{
    QVector<QVariant> res;
    res.clear();;
    return res;
}

void ImageToXYZ::setParameters(QVector<QVariant> p)
{
    Q_UNUSED(p);
}
