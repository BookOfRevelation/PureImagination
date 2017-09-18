#include "stalactiteeffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

StalactiteEffect::StalactiteEffect(const QString& n)
    : PureFilter(n)
{
    widget = new StalactiteWidget();
}

StalactiteEffect::~StalactiteEffect()
{
   delete widget;
}

bool StalactiteEffect::init()
{
    return (widget->exec() == QDialog::Accepted);
}

void StalactiteEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    const int thick = widget->thickness;

    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);
        for(int i = 0; i < img.width() ; i = i + thick)
        {
            for(int j = img.height() -1 ; j >= 0 ; --j)
            {
                float coeff = static_cast<float>(widget->variance)/100.0f;

                float delta = static_cast<float>(widget->push) * coeff;

                int decallage = PureCore::getRandom(widget->push - delta, widget->push + delta);

                //appliquer sur toute la bande
                for(int d = 0 ; d < thick ; ++d)
                {
                    if(j-decallage >= 0)
                    {
                        img.setPixelColor(i+d, j, img.pixelColor(i+d, j-decallage ));
                    }

                }
            }
        }
    }
}

QWidget* StalactiteEffect::getParamWidget()
{
    return widget;
}

QVector<QVariant> StalactiteEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(widget->thickness));
    res.push_back(QVariant(widget->variance));
    res.push_back(QVariant(widget->push));

    return res;
}

void StalactiteEffect::setParameters(QVector<QVariant> p)
{
    widget->thickness = p[0].toInt();
    widget->variance = p[1].toInt();
    widget->push = p[2].toInt();

    widget->updateUI();
}

StalactiteWidget::StalactiteWidget()
    : QDialog()
{
    thickness = 1;
    variance = 0;
    push = 1;
    setWindowTitle("param");
    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);

    thickSS = new SlideSpiner("Épaisseur : ", "px", 1, 1, 20);
    varianceSS = new SlideSpiner("Variance : ", "%", 1, 0, 100);
    pushSS = new SlideSpiner("Push : ", "px", 1, 1, 200);
    processButton = new QPushButton("Ok");
    randomizeButton = new QPushButton("Randomize");

    mainLt->addWidget(thickSS);
    mainLt->addWidget(varianceSS);
    mainLt->addWidget(pushSS);
    mainLt->addWidget(processButton);
    mainLt->addWidget(randomizeButton);

    this->setLayout(mainLt);

    connect(processButton, &QPushButton::pressed, this, [this]()
    {
       thickness = thickSS->getValue();
       variance = varianceSS->getValue();
       push = pushSS->getValue();

       this->accept();
    });
    connect(randomizeButton, &QPushButton::pressed, this, &StalactiteWidget::randomize);
}

void StalactiteWidget::randomize()
{
    variance = PureCore::getRandom(varianceSS->getMinimum(),varianceSS->getMaximum());
    thickness = PureCore::getRandom(thickSS->getMinimum(),thickSS->getMaximum());
    push = PureCore::getRandom(pushSS->getMinimum(),pushSS->getMaximum());

    updateUI();
}
