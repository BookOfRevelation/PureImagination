#include "oldvcreffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>

OldVcrEffect::OldVcrEffect(const QString &n)
    : PureFilter(n)
{
    gemwidget = new OldVcrWidget();
}

OldVcrEffect::~OldVcrEffect()
{
    delete gemwidget;
}

bool OldVcrEffect::init()
{
   return (gemwidget->exec() == QDialog::Accepted);
}

void OldVcrEffect::process()
{
    int rate = gemwidget->rate;

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);

        int width = img.width();
        int height = img.height();
        int bw = gemwidget->bw;
        int zone = 0;
        float deco = 0.8;


        float factor = rate;



        for(int j = 0 ; j < height ; j = j + bw)
        {
            for(int i = 0 ; i < width ; ++i)
            {
                for(int k = 0 ; k < bw ; ++k)
                {
                    int newJ = j+k;
                    if(newJ >= height)
                    {
                        newJ = height - 1;
                    }
                    QColor bc = img.pixelColor(i,newJ);
                    if(zone%3 == 0)
                    {
                        int red = bc.red()   * factor;
                        int green = bc.green()/deco ;
                        int blue = bc.blue()  /deco;
                        if(red > 254)
                        {
                            red = 254;
                        }
                        if(green > 254)
                        {
                            green = 254;
                        }
                        if(blue > 254)
                        {
                            blue = 254;
                        }

                        bc.setRgb(red, green, blue);
                        //tout en rouge
                        img.setPixelColor(i, newJ, bc);
                    }
                    else if(zone%3 == 1)
                    {
                        int red = bc.red() /deco  ;
                        int green = bc.green() * factor;
                        int blue = bc.blue() /deco ;
                        if(red > 254)
                        {
                            red = 254;
                        }
                        if(green > 254)
                        {
                            green = 254;
                        }
                        if(blue > 254)
                        {
                            blue = 254;
                        }

                        bc.setRgb(red, green, blue);
                        //tout en vert
                        img.setPixelColor(i, newJ, bc);
                    }
                    else if(zone%3==2)
                    {
                        int red = bc.red()    /deco  ;
                        int green = bc.green()/deco ;
                        int blue = bc.blue()  * factor;
                        if(red > 254)
                        {
                            red = 254;
                        }
                        if(green > 254)
                        {
                            green = 254;
                        }
                        if(blue > 254)
                        {
                            blue = 254;
                        }

                        bc.setRgb(red, green, blue);
                        //tout en bleu
                        img.setPixelColor(i, newJ, bc);
                    }


                }

            }
            zone = zone + 1;
        }





    }
}


QWidget* OldVcrEffect::getParamWidget()
{
    return gemwidget;
}

QVector<QVariant> OldVcrEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(gemwidget->rate));
    res.push_back(QVariant(gemwidget->bw));

    return res;
}

void OldVcrEffect::setParameters(QVector<QVariant> p)
{
    gemwidget->rate = p[0].toInt();
    gemwidget->bw = p[1].toInt();

    gemwidget->updateUI();
}

OldVcrWidget::OldVcrWidget()
    : QDialog()
{
    setWindowTitle("param");
    rate = 1;
    bw = 1;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    rateSS = new SlideSpiner("Color factor : ", "", 2, 1, 4);
    bwSS = new SlideSpiner("Band heigth: ", "px", 1, 1, 10);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(rateSS);
    mainLt->addWidget(bwSS);
    QPushButton* randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &OldVcrWidget::randomize);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(bwSS, SlideSpiner::valueChanged, this, OldVcrWidget::onBwModified);
    connect(rateSS, SlideSpiner::valueChanged, this, OldVcrWidget::onRateModified);
    connect(processBtn, QAbstractButton::pressed, this, &QDialog::accept);
}

void OldVcrWidget::randomize()
{
    rate = PureCore::getRandom(rateSS->getMinimum(), rateSS->getMaximum());
    bw = PureCore::getRandom(bwSS->getMinimum(), bwSS->getMaximum());

    updateUI();
}

void OldVcrWidget::onRateModified(double v)
{
    rate = v;
}

void OldVcrWidget::onBwModified(double v)
{
    bw = v;
}

