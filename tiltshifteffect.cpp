#include "tiltshifteffect.h"
#include "pureimage.h"
#include <QGraphicsBlurEffect>
#include <QDebug>

TiltShiftEffect::TiltShiftEffect(const QString &n)
    : PureFilter(n)
{
}

TiltShiftEffect::~TiltShiftEffect()
{

}

bool TiltShiftEffect::init()
{
    return true;
}

void TiltShiftEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {


        //image de base
        QImage& img = data->getImage(nbimg);


        //get top and bottom image
        //take 15%
        int ratio = 25;
        const int blurCount = 10;
        const qreal blurMax = 8;
        int height = (img.height()*ratio)/100;


        QImage top = img.copy(0,0, img.width(), height);
        QImage bot = img.copy(0, img.height()-height, img.width(), height);

        for(int i = 0 ; i < blurCount ; ++i)
        {

            qreal newHeight = (static_cast<double>((blurCount-i)))/(static_cast<double>(blurCount));
            newHeight *= top.height();
            QImage btop = top.copy(0,0, top.width(),newHeight);
            QImage bbot = bot.copy(0, newHeight, bot.width(), bot.height() - newHeight);

            btop = PureCore::applyEffectToImage(btop, blurMax/static_cast<double>(blurCount));
            bbot = PureCore::applyEffectToImage(bbot, 4);

            for(int x = 0 ; x < top.width() ; ++x)
            {
                for(int y = 0 ; y < top.height() ; ++y)
                {
                    if(y < btop.height())
                    {
                        top.setPixelColor(x,y, btop.pixelColor(x,y));
                    }
                    if(y < bbot.height())
                    {
                        bot.setPixelColor(x, y, bbot.pixelColor(x,y));
                    }
                }
            }

        }


        for(int i = 0 ; i < img.width() ; ++i)
        {
            for(int j = 0 ; j < img.height() ; ++j)
            {
                QColor rc = img.pixelColor(i,j);

                if(j < height)
                {
                    rc = top.pixelColor(i,j);
                }
                else if(j >= img.height()-height)
                {
                    rc = bot.pixelColor(i, j - (img.height()-height) );
                }


                img.setPixelColor(i, j, rc);
            }
        }

    }



}



