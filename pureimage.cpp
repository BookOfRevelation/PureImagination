#include "pureimage.h"

PureImage::PureImage()
    : PureData()
{
    clear();
}

int PureImage::getImageCount() const
{
    return images.count();
}

QImage& PureImage::getImage(int i)
{
    return images[i].first;
}

QString PureImage::getName(int i) const
{
    return images[i].second;
}

void PureImage::addImage(QImage img, const QString &name)
{
    images.push_back(QPair<QImage, QString>(img,name));
}

void PureImage::clear()
{
    images.clear();
}
