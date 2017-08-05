#include "symbioticmesseffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

SymbioticMessEffect::SymbioticMessEffect()
    : PureFilter()
{
    gemwidget = new SymbioticMessWidget();
}

SymbioticMessEffect::~SymbioticMessEffect()
{
    delete gemwidget;
}

bool SymbioticMessEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);

}

void SymbioticMessEffect::process()
{
    int rate = gemwidget->rate;

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);

        int width = img.width();
        int height = img.height();

        //how many % we fuck up the image
        int rration = PureCore::getRandom(0,rate);
        int gration = PureCore::getRandom(0,rate);
        int bration = PureCore::getRandom(0,rate);




        for(int i = 0 ; i < width ; ++i)
        {
            for(int j = 0; j < height ; ++j)
            {
                int chance = PureCore::getRandom(0,100);
                if(chance <= gemwidget->chance)
                {
                    QColor baseC = img.pixelColor(i,j);

                    int totalR = (baseC.red()*rration/100);
                    int totalG = (baseC.green()*gration/100);
                    int totalB = (baseC.blue()*bration/100);

                    totalR = totalR - (totalR/2);
                    totalG = totalG - (totalG/2);
                    totalB = totalB - (totalB/2);

                    int rsign = (PureCore::getRandom(0,1) == 0 ? 1 : -1);
                    int gsign = (PureCore::getRandom(0,1) == 0 ? 1 : -1);
                    int bsign = (PureCore::getRandom(0,1) == 0 ? 1 : -1);

                    totalR *= rsign;
                    totalG *= gsign;
                    totalB *= bsign;


                    int finalR = baseC.red() + totalR;
                    if(finalR > 254)
                    {
                        finalR = 254;
                    }
                    else if(finalR < 0)
                    {
                        finalR = 0;
                    }

                    int finalG = baseC.green() + totalG;
                    if(finalG > 254)
                    {
                        finalG = 254;
                    }
                    else if(finalG < 0)
                    {
                        finalG = 0;
                    }

                    int finalB = baseC.blue() + totalB;
                    if(finalB > 254)
                    {
                        finalB = 254;
                    }
                    else if(finalB < 0)
                    {
                        finalB = 0;
                    }

                    baseC.setRgb(finalR,finalG,finalB);

                    img.setPixelColor(i,j, baseC);
                }

            }
        }

    }

}


QWidget* SymbioticMessEffect::getParamWidget()
{
    return gemwidget;
}


SymbioticMessWidget::SymbioticMessWidget()
    : QDialog()
{
    rate = 1;
    chance = 1;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    chanceSS = new SlideSpiner("Mess density : ", "%", 1, 1, 100);
    rateSS = new SlideSpiner("Mess force : ", "%", 1, 1, 100);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(chanceSS);
    mainLt->addWidget(rateSS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(rateSS, SlideSpiner::valueChanged, this, SymbioticMessWidget::onRateModified);
    connect(chanceSS, SlideSpiner::valueChanged, this, SymbioticMessWidget::onChanceModified);
    connect(processBtn, QAbstractButton::pressed, this, &QDialog::accept);

}


void SymbioticMessWidget::onRateModified(double v)
{
    rate = v;
}

void SymbioticMessWidget::onChanceModified(double v)
{
    chance = v;
}
