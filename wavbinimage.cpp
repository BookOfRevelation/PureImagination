#include "wavbinimage.h"
#include "pureaudio.h"
#include "pureimage.h"
#include <QInputDialog>
#include <QtMath>

#include <QDebug>

WavBinWidget::WavBinWidget()
{
    size = 64;
    sizeSd = new SlideSpiner("Image size", "px", 1, 64, 1000);
    ok = new QPushButton("Ok");
    mainLt = new QBoxLayout(QBoxLayout::TopToBottom);

    mainLt->addWidget(sizeSd);
    mainLt->addWidget(ok);

    this->setLayout(mainLt);

    connect(ok, &QPushButton::pressed, this, &WavBinWidget::goPressed);
}

void WavBinWidget::goPressed()
{
    size = sizeSd->getValue();

    this->accept();
}

WavBinImage::WavBinImage(const QString &n)
    : PureTransformater(n)
{
    w = new WavBinWidget;
}

bool WavBinImage::init()
{
    return w->exec() == QDialog::Accepted;
}

void WavBinImage::process()
{
    PureAudio* wav = static_cast<PureAudio*>(PureCore::currentData);

    int count = wav->sampleCount();

    int cote = qFloor(qSqrt(count)/3);

    QImage img(cote, cote+1,QImage::Format_RGB32);
    img.fill(Qt::black);

    int max = wav->getMaximumValue();
    int min = wav->getMinimumValue();
    qDebug()<<"max : "<<max;
    qDebug()<<"min : "<<min;
    max -= min;
    min = 0;
    float ratio = qAbs((float)(max)/255.0f);

    for(int i = 0; i < cote ; ++i)
    {
        for(int j = 0 ; j < cote ; j++)
        {
            QColor c(0,0,0);

            int redColor = qAbs(wav->getValue((i*cote+j)%wav->sampleCount())/ratio);

            int greenColor = qAbs(wav->getValue((i*cote+j+1)%wav->sampleCount())/ratio);
            int blueColor = qAbs(wav->getValue((i*cote+j+2)%wav->sampleCount())/ratio);

            c.setRgb(redColor, greenColor, blueColor);

            img.setPixelColor(i, j, c);

        }

    }
    img = img.scaled(w->size, w->size);
    PureImage* newData = new PureImage();

    newData->addImage(img, wav->getName().split(".")[0]+QString(".jpg"));

    delete wav;

    PureCore::currentData = newData;

}

QVector<QVariant> WavBinImage::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(w->size));

    return res;
}

void WavBinImage::setParameters(QVector<QVariant> p)
{
    w->size = p[0].toInt();

    w->updateUI();
}
