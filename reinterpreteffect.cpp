#include "reinterpreteffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

ReinterpretEffect::ReinterpretEffect(const QString& n)
    : PureFilter(n)
{

}


bool ReinterpretEffect::init()
{
    return true;
}

void ReinterpretEffect::process()
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

                float rf = pc.redF();
                int* pi = reinterpret_cast<int*>(&rf);
                pc.setRed((*pi)%255);

                rf = pc.greenF();
                pi = reinterpret_cast<int*>(&rf);
                pc.setGreen((*pi)%255);

                rf = pc.blueF();
                pi = reinterpret_cast<int*>(&rf);
                pc.setBlue((*pi)%255);

                img.setPixelColor(i, j, pc);

            }
        }

    }
}

QVector<QVariant> ReinterpretEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    return res;
}

void ReinterpretEffect::setParameters(QVector<QVariant> p)
{
    Q_UNUSED(p);
}

QWidget* ReinterpretEffect::getParamWidget()
{
    return nullptr;
}
