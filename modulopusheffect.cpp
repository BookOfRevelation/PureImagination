#include "modulopusheffect.h"
#include "purecore.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

ModuloPushEffect::ModuloPushEffect()
    : PureFilter(),sequence(false), targetDir("")
{
    gemwidget = new ModuloPushWidget(this);

}
DataWidget* ModuloPushEffect::getDataWidget()
{
    return dataW;
}

ModuloPushEffect::~ModuloPushEffect()
{
    delete gemwidget;
}

bool ModuloPushEffect::init()
{
   return (gemwidget->exec() == QDialog::Accepted);

}

void ModuloPushEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);

        int width = img.width();
        int height = img.height();

        float effectiveH = PureCore::getRandom(gemwidget->minH, gemwidget->maxH);
        float effectiveW = PureCore::getRandom(gemwidget->minW, gemwidget->maxW);

        int decalage = width * (effectiveH/100.0);
        int largeur = height * (effectiveW/100.0);
        int repeat = largeur;
        //extract all pixels

        while(repeat < img.height())
        {
            int offset = repeat - largeur;
            QImage subImage = img.copy(0, offset, width, largeur);
            const QImage subref = subImage;
            for(int i = 0 ; i < subImage.width() ;  i++)
            {
                for(int j = 0 ; j < subImage.height() ; ++j)
                {
                    img.setPixelColor((i + decalage)%subImage.width(), (j+offset), subref.pixelColor(i, j));
                }
            }

            effectiveW = PureCore::getRandom(gemwidget->minH, gemwidget->maxH);
            largeur = height * (effectiveW/100.0);
            effectiveH = PureCore::getRandom(gemwidget->minW, gemwidget->maxW);

            decalage = width * (effectiveH/100.0);

            repeat += largeur;
        }
    }

}


QWidget* ModuloPushEffect::getParamWidget()
{
    return gemwidget;
}


ModuloPushWidget::ModuloPushWidget(ModuloPushEffect* effect)
    : QDialog(), burgle(effect)
{
    setWindowTitle("param");

    minH = 1;
    maxH = 1;
    minW = 1;
    maxW = 1;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    minHSS = new SlideSpiner("Décallage minimum : ", "%", 1, 1, 99);
    maxHSS = new SlideSpiner("Décallage maximum : ", "%", 1, 1, 99);

    minWSS = new SlideSpiner("Largeur minimale : ", "%", 1, 1, 99);
    maxWSS = new SlideSpiner("Largeur maximale : ", "%", 1, 1, 99);

    processBtn = new QPushButton("Ok");

    mainLt->addWidget(minHSS);
    mainLt->addWidget(maxHSS);
    mainLt->addWidget(minWSS);
    mainLt->addWidget(maxWSS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(minHSS, SlideSpiner::valueChanged, this, ModuloPushWidget::onMinHModified);
    connect(maxHSS, SlideSpiner::valueChanged, this, ModuloPushWidget::onMaxHModified);
    connect(minWSS, SlideSpiner::valueChanged, this, ModuloPushWidget::onMinWModified);
    connect(maxWSS, SlideSpiner::valueChanged, this, ModuloPushWidget::onMaxWModified);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);

}


void ModuloPushWidget::onMinHModified(double v)
{
    minH = v;
    maxHSS->setMinimum(v);
}

void ModuloPushWidget::onMaxHModified(double v)
{
    maxH = v;
    minHSS->setMaximum(v);
}

void ModuloPushWidget::onMinWModified(double v)
{
    minW = v;
    maxWSS->setMinimum(v);
}

void ModuloPushWidget::onMaxWModified(double v)
{
    maxW = v;
    minWSS->setMaximum(v);
}
