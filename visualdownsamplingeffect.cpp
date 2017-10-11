#include "visualdownsamplingeffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>

VisualDownSamplingEffect::VisualDownSamplingEffect(const QString &n)
    : PureFilter(n)
{
    gemwidget = new VisualDownSamplingWidget();
}

VisualDownSamplingEffect::~VisualDownSamplingEffect()
{
    delete gemwidget;
}

bool VisualDownSamplingEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);


}

void VisualDownSamplingEffect::process()
{
    const int rate = gemwidget->rate;

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);

        int width = img.width();
        int height = img.height();


        const int squareL = (width * rate)/1000;

        for(int i = 0 ; i < width+squareL ; i += squareL)
        {
            for(int j = 0; j < height+squareL ; j+= squareL)
            {
                int geti = i;
                int getj = j;
                if(geti >= width)
                {
                    geti = width-1;
                }
                if(getj >= height)
                {
                    getj = height-1;
                }
                QColor pix = img.pixelColor(geti,getj);

                for(int w = -squareL/2 ; w < squareL/2 ; ++w)
                {
                    for(int h = -squareL/2 ; h < squareL/2 ; ++h)
                    {
                        int newi = i +w;
                        int newj = j + h;
                        if(newi >= width || newi < 0 || newj >= height || newj < 0)
                        {
                            continue;
                        }

                        img.setPixelColor(newi, newj, pix);
                    }
                }
            }
        }
    }
}


QWidget* VisualDownSamplingEffect::getParamWidget()
{
    return gemwidget;
}

QVector<QVariant> VisualDownSamplingEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(gemwidget->rate));

    return res;
}

void VisualDownSamplingEffect::setParameters(QVector<QVariant> p)
{
    gemwidget->rate = p[0].toInt();

    gemwidget->updateUI();
}

VisualDownSamplingWidget::VisualDownSamplingWidget()
    : QDialog()
{
    setWindowTitle("param");
    rate = 1;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    rateSS = new SlideSpiner("Bitcrushing : ", "%", 1, 1, 99);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(rateSS);


    QPushButton* randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &VisualDownSamplingWidget::randomize);

    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(rateSS, &SlideSpiner::valueChanged, this, &VisualDownSamplingWidget::onRateModified);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);


}

void VisualDownSamplingWidget::randomize()
{
    rate = PureCore::getRandom(rateSS->getMinimum(), rateSS->getMaximum());

    updateUI();
}


void VisualDownSamplingWidget::onRateModified(double v)
{
    rate = v;
}
