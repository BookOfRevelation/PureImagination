#include "purecondition.h"

PureCondition::PureCondition()
{
}

PureCondition::~PureCondition()
{

}

void PureCondition::init()
{
    checkTable.clear();
    PureImage* data = static_cast<PureImage*>(PureCore::noFragement);


    for(int nb = 0 ; nb < data->getImageCount() ; ++nb)
    {

        QImage img = data->getImage(nb);


        QVector<QVector<bool>> ivec;
        ivec.clear();
        for(int i = 0 ; i < img.width(); ++i)
        {
            QVector<bool> jvec;
            jvec.clear();

            for(int j = 0 ; j < img.height(); ++j)
            {
                jvec.push_back(addPixel(img, i, j));
            }
            ivec.push_back(jvec);
        }

        checkTable.push_back(ivec);
    }

}

bool PureCondition::checkPixel(int n, int x, int y)
{
    return checkTable[n][x][y];
}


EvenCondition::EvenCondition()
    : PureCondition()
{

}


bool EvenCondition::addPixel(const QImage &ref, int x, int y)
{
    Q_UNUSED(ref);

    return ((y)%20 == 0);
}
