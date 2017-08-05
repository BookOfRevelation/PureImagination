#include "ghostfusioneffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

GhostFusionEffect::GhostFusionEffect()
    : PureFilter(), fileName("")
{

}

bool GhostFusionEffect::init()
{
    return true;
}

void GhostFusionEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    QString name = data->getName(0);
    QImage ref = data->getImage(0);
    for(int i = 1 ; i < data->getImageCount() ; i++)
    {
        QImage& img = data->getImage(i);
        img = img.scaled(ref.width(), ref.height());
    }
    QImage newImage(ref.width(), ref.height(), ref.format());
    for(int w = 0 ; w < ref.width() ; ++w)
    {
        for(int h = 0 ; h < ref.height() ; ++h)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            for(int i = 0 ; i < data->getImageCount(); ++i)
            {
                QColor pc = data->getImage(i).pixelColor(w,h);

                red += pc.red();
                green += pc.green();
                blue += pc.blue();
            }

            newImage.setPixelColor(w, h, QColor(
                                       red/data->getImageCount(),
                                       green/data->getImageCount(),
                                       blue/data->getImageCount()
                                       ));

        }
    }

    data->clear();
    data->addImage(newImage, name);

}
