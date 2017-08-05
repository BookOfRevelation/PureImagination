#include "hsvtorgb.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"


HsvToRgb::HsvToRgb()
    : PureFilter(), sequence(false), targetDir("")
{
}

HsvToRgb::~HsvToRgb()
{
}

bool HsvToRgb::init()
{
   return true;

}

void HsvToRgb::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int i  = 0 ; i < data->getImageCount() ;  ++i)
    {
        //image de base
        QImage& img = data->getImage(i);

        int width = img.width();
        int height = img.height();

        for(int i = 0 ; i < width ; ++i)
        {
            for(int j = 0; j < height ; ++j)
            {
                QColor pc = img.pixelColor(i,j);

                QColor toRGB;
                toRGB.setRgb((pc.hue()*255)/360, pc.saturation(), pc.value());

                img.setPixelColor(i, j, toRGB);
            }
        }

    }
}


QWidget* HsvToRgb::getParamWidget()
{
    return nullptr;
}

