#include "xyztoimg.h"
#include <QImage>
#include <QVariant>
#include <QDebug>
XYZToImg::XYZToImg(const QString& n)
    : PureTransformater(n)
{

}

bool XYZToImg::init()
{
    return true;
}

void XYZToImg::process()
{
    //max is 1067
    //min is 0
    PureXYZ* xyz = static_cast<PureXYZ*>(PureCore::currentData);
    PureImage* img = new PureImage();

    QImage base(xyz->width(), xyz->height(), QImage::Format_ARGB32);

    for(int i = 0 ; i < xyz->count() ; ++i)
    {
        QVector3D pt = xyz->getPoint(i);

        int r, g, b;

        r = pt.z() / 4.18;
        g = static_cast<int>(pt.z()) % 255;
        b = (pt.z()*255)/1067;


//        int hue = (pt.z()*360.0f)/1067.0f;
//        int sum = (pt.z()*200.0f)/1067.0f;

//        int saturation = 100;
//        int luminance = sum/2;

//        base.setPixelColor(pt.x(), pt.y(), QColor::fromHsl(hue, saturation, luminance));

        base.setPixelColor(pt.x(), pt.y(), QColor(r,g,b));
    }

    img->addImage(base, "xyzToImg");

    delete xyz;

    PureCore::currentData = img;

}
