#include "noizifiereffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

NoizifierEffect::NoizifierEffect(const QString &n)
    : PureFilter(n),sequence(false), targetDir("")
{
    gemwidget = new NoizifierWidget(this);
}

NoizifierEffect::~NoizifierEffect()
{
    delete gemwidget;
}

bool NoizifierEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);

}

void NoizifierEffect::process()
{
    int rate = gemwidget->rate;

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);

        int width = img.width();
        int height = img.height();

        for(int i = 0 ; i < width ; ++i)
        {
            for(int j = 0; j < height ; ++j)
            {
                int tirage = PureCore::getRandom(0,100);
                if(tirage < rate)
                {
                    int colors[3];

                    for(int k = 0 ; k < 3 ; ++k)
                    {
                        colors[k] = PureCore::getRandom(0,254);
                    }
                    img.setPixelColor(i,j, QColor(colors[0],colors[1],colors[2]));
                }
            }
        }

    }

}


QWidget* NoizifierEffect::getParamWidget()
{
    return gemwidget;
}


NoizifierWidget::NoizifierWidget(NoizifierEffect* effect)
    : QDialog(), burgle(effect)
{
    rate = 1;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    rateSS = new SlideSpiner("Noise rate : ", "%", 1, 1, 100);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(rateSS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(rateSS, SlideSpiner::valueChanged, this, NoizifierWidget::onRateModified);
    connect(processBtn, QAbstractButton::pressed, this, &QDialog::accept);

}


void NoizifierWidget::onRateModified(double v)
{
    rate = v;
}
