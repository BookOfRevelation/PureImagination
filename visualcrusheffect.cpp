#include "visualcrusheffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

VisualCrushEffect::VisualCrushEffect()
    : PureFilter()
{
    gemwidget = new VisualCrushWidget();
}

VisualCrushEffect::~VisualCrushEffect()
{
    delete gemwidget;
}

bool VisualCrushEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);

}

void VisualCrushEffect::process()
{
    const int max = 255;
    const int rate = gemwidget->rate;

    const int step = (rate*max)/100;
    int* LUT = new int[max];
    int val = 0;
    for(int i = 0 ; i < max ;++i)
    {
        if(i%step == 0)
        {
            LUT[i] = i;
            val = i;
        }
        else
        {
            LUT[i] = val;
        }
    }

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
                QColor realColor = img.pixelColor(i,j);

                img.setPixelColor(i, j, QColor(LUT[realColor.red()],LUT[realColor.green()], LUT[realColor.blue()]));
            }
        }

    }

    delete[] LUT;
}


QWidget* VisualCrushEffect::getParamWidget()
{
    return gemwidget;
}


VisualCrushWidget::VisualCrushWidget()
    : QDialog()
{
    rate = 1;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    rateSS = new SlideSpiner("Bitcrushing : ", "%", 1, 1, 99);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(rateSS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(rateSS, SlideSpiner::valueChanged, this, VisualCrushWidget::onRateModified);
    connect(processBtn, QAbstractButton::pressed, this, &QDialog::accept);

}


void VisualCrushWidget::onRateModified(double v)
{
    rate = v;
}
