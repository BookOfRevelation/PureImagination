#include "rgbtohsv.h"
#include "pureimage.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>


RgbToHsv::RgbToHsv()
    : PureFilter(),sequence(false), targetDir("")
{
}

RgbToHsv::~RgbToHsv()
{
}

bool RgbToHsv::init()
{
    return true;

}

void RgbToHsv::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);

    for(int im  = 0 ; im < data->getImageCount() ;  ++im)
    {

        //image de base
        QImage& img = data->getImage(im);

        int width = img.width();
        int height = img.height();

        for(int i = 0 ; i < width ; ++i)
        {
            for(int j = 0; j < height ; ++j)
            {
                QColor pc = img.pixelColor(i,j);

                QColor toHSV;
                toHSV.setHsv((pc.red()*360)/255, pc.green(), pc.blue());

                img.setPixelColor(i, j, toHSV);
            }
        }

    }
}


QWidget* RgbToHsv::getParamWidget()
{
    return nullptr;
}

