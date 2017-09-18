#include "fragmenttoimage.h"
#include "purecondition.h"


FragmentToImage::FragmentToImage(const QString& n)
    : PureTransformater(n)
{

}

FragmentToImage::~FragmentToImage()
{
}

bool FragmentToImage::init()
{
   return (PureCore::noFragement != nullptr);
}

void FragmentToImage::process()
{
    PureImage* gldata = static_cast<PureImage*> (PureCore::currentData);
    PureImage* olddata = static_cast<PureImage*>(PureCore::noFragement);

    for(int i = 0 ; i < gldata->getImageCount() ; ++i)
    {
        QImage& img = olddata->getImage((i%olddata->getImageCount()));
        QImage& newimg = gldata->getImage(i);

        for(int x = 0; x < img.width() ; ++x)
        {
            for(int j = 0; j < img.height() ; ++j)
            {
                if(!PureCore::condition->checkPixel(i, x, j))
                {
                    newimg.setPixelColor(x,j, img.pixelColor(x, j));
                }
            }
        }
    }

    delete PureCore::noFragement;
    PureCore::noFragement = nullptr;

    delete PureCore::condition;
    PureCore::condition = nullptr;
}

void FragmentToImage::setParameters(QVector<QVariant> p)
{
    Q_UNUSED(p);
}

QVector<QVariant> FragmentToImage::getParameters() const
{
    QVector<QVariant> v;
    v.clear();
    return v;
}

