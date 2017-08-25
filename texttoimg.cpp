#include "texttoimg.h"
#include "puretext.h"
#include "pureimage.h"
#include <QtMath>
#include <QDebug>
TextToImg::TextToImg(const QString& n)
    : PureTransformater(n)
{

}

bool TextToImg::init()
{
    return true;
}

void TextToImg::process()
{
    PureText* txt = static_cast<PureText*>(PureCore::currentData);
    int count = txt->getText().size();
    int cote = qFloor(qSqrt(count)/3);
    QImage img(cote, cote+1, QImage::Format_RGB32);
    img.fill(Qt::black);
    int cx = 0;
    for(int i = 0 ; i < cote ; ++i)
    {
        for(int j = 0 ; j < cote ; ++j)
        {
            QChar c1 = txt->getText().at(cx++);
            QChar c2 = txt->getText().at(cx++);
            QChar c3 = txt->getText().at(cx++);

            int v1 = c1.unicode()%256;
            int v2 = c2.unicode()%256;
            int v3 = c3.unicode()%256;
            QColor color(v1,v2,v3 );

            img.setPixelColor(i, j, color);
        }
    }
    PureImage* newData = new PureImage();
    newData->addImage(img, "textimg.jpg");
    delete txt;
    PureCore::currentData = newData;

}


QVector<QVariant> TextToImg::getParameters() const
{
    QVector<QVariant> res;
    res.clear();
    return res;
}

void TextToImg::setParameters(QVector<QVariant> p)
{
    Q_UNUSED(p);
}
