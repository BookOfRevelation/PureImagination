#include "retriggereffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include "purecore.h"
#include "pureimage.h"


RetriggerEffect::RetriggerEffect(const QString &n)
    :  PureFilter(n)
{
    gemwidget = new RetriggerWidget();
}

RetriggerEffect::~RetriggerEffect()
{
    delete gemwidget;
}

bool RetriggerEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);

}

void RetriggerEffect::process()
{

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);
        int number = PureCore::getRandom(gemwidget->numberMin, gemwidget->numberMax);
        for(int k = 0; k < number ; ++k)
        {
            int decalx = PureCore::getRandom(gemwidget->minOffsetW, gemwidget->maxOffsetW);
            int decalh = PureCore::getRandom(gemwidget->minOffsetH, gemwidget->maxOffsetH);
            int echoNb = PureCore::getRandom(gemwidget->repeatMin, gemwidget->repeatMax);
            //image de base

            int width = img.width();
            int height = img.height();
            //calcul du % de width


            for(int echo = 0 ; echo < echoNb ; ++echo)
            {
                float effectiveH = PureCore::getRandom(gemwidget->minH, gemwidget->maxH);


                int squareW = width * (effectiveH/100.0);

                //calcul du % de height
                float effectiveW = PureCore::getRandom(gemwidget->minW, gemwidget->maxW);
                int squareH = height * (effectiveW/100.0);
                float startx = PureCore::getRandom(0, width - squareW);
                float starty = PureCore::getRandom(0, height - squareH);



                int stepsx = (decalx / echoNb) + 1;
                int stepy = (decalh/echoNb) + 1;


                QImage subrect = img.copy(startx, starty, squareW, squareH);

                for(int i = 0 ; i < subrect.width() ; ++i)
                {
                    for(int j = 0 ; j < subrect.height() ; ++j)
                    {
                        img.setPixelColor((int)(i+startx+decalx + stepsx*echo)%width, (int)(j+starty+decalh + stepy*echo)%height, subrect.pixelColor(i,j));
                    }
                }
            }



        }
    }

}


QWidget* RetriggerEffect::getParamWidget()
{
    return gemwidget;
}


QVector<QVariant> RetriggerEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(gemwidget->minH);
    res.push_back(gemwidget->maxH);
    res.push_back(gemwidget->minW);
    res.push_back(gemwidget->maxW);
    res.push_back(gemwidget->minOffsetH);
    res.push_back(gemwidget->maxOffsetH);
    res.push_back(gemwidget->minOffsetW);
    res.push_back(gemwidget->maxOffsetW);
    res.push_back(gemwidget->repeatMin);
    res.push_back(gemwidget->repeatMax);
    res.push_back(gemwidget->numberMin);
    res.push_back(gemwidget->numberMax);

    return res;
}

void RetriggerEffect::setParameters(QVector<QVariant> p)
{
    gemwidget->minH = p[0].toInt();
    gemwidget->maxH = p[1].toInt();
    gemwidget->minW = p[2].toInt();
    gemwidget->maxW = p[3].toInt();
    gemwidget->minOffsetH = p[4].toInt();
    gemwidget->maxOffsetH = p[5].toInt();
    gemwidget->minOffsetW = p[6].toInt();
    gemwidget->maxOffsetW = p[7].toInt();
    gemwidget->repeatMin = p[8].toInt();
    gemwidget->repeatMax = p[9].toInt();
    gemwidget->numberMin = p[10].toInt();
    gemwidget->numberMax = p[11].toInt();

    gemwidget->updateUI();
}



RetriggerWidget::RetriggerWidget()
    : QDialog(), minH(1), maxH(1), minW(1), maxW(1), minOffsetH(1),
      maxOffsetH(1), minOffsetW(1), maxOffsetW(1),
      repeatMin(1), repeatMax(1), numberMin(1), numberMax(1)
{
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    minHSS = new SlideSpiner("Longueur minimale : ", "%", 1, 1, 99);
    maxHSS = new SlideSpiner("Longueur maximale : ", "%", 1, 1, 99);

    minWSS = new SlideSpiner("Hauteur minimale : ", "%", 1, 1, 99);
    maxWSS = new SlideSpiner("Hauteur maximale : ", "%", 1, 1, 99);


    offsetWmnSS = new SlideSpiner("Offset de longueur minimal : ", "px", 1, 1, 300);
    offsetWmxSS = new SlideSpiner("Offset de longueur maximal : ", "px", 1, 1, 300);

    offsetHmnSS = new SlideSpiner("Offset de hauteur minimal : ", "px", 1, 1, 300);
    offsetHmxSS = new SlideSpiner("Offset de hauteur maximal : ", "px", 1, 1, 300);


    minRptSS = new SlideSpiner("Nombre d'échos minimal : ", "", 1, 1, 100);
    maxRptSS = new SlideSpiner("Nombre d'échos maximal : ", "", 1, 1, 100);

    minNbSS = new SlideSpiner("Nombre de retrigging minimal : ", "", 1, 1, 100);
    maxNbSS = new SlideSpiner("Nombre de retrigging maximal : ", "", 1, 1, 100);


    processBtn = new QPushButton("Ok");

    mainLt->addWidget(minHSS);
    mainLt->addWidget(maxHSS);
    mainLt->addWidget(minWSS);
    mainLt->addWidget(maxWSS);

    mainLt->addWidget(offsetWmnSS);
    mainLt->addWidget(offsetWmxSS);
    mainLt->addWidget(offsetHmnSS);
    mainLt->addWidget(offsetHmxSS);

    mainLt->addWidget(minRptSS);
    mainLt->addWidget(maxRptSS);
    mainLt->addWidget(minNbSS);
    mainLt->addWidget(maxNbSS);

    QPushButton* randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &RetriggerWidget::randomize);

    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(minHSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMinHModified);
    connect(maxHSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMaxHModified);
    connect(minWSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMinWModified);
    connect(maxWSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMaxWModified);

    connect(offsetWmnSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMinOffsetWModified);
    connect(offsetWmxSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMaxOffsetWModified);
    connect(offsetHmnSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMinOffsetHModified);
    connect(offsetHmxSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onMaxOffsetHModified);

    connect(minRptSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onRepeatMinModified);
    connect(maxRptSS, &SlideSpiner::valueChanged, this, &RetriggerWidget::onRepeatMaxModified);
    connect(minNbSS,  &SlideSpiner::valueChanged, this, &RetriggerWidget::onNumberMinModified);
    connect(maxNbSS,  &SlideSpiner::valueChanged, this, &RetriggerWidget::onNumberMaxModified);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);

}

void RetriggerWidget::randomize()
{
    maxH = PureCore::getRandom(maxHSS->getMinimum(), maxHSS->getMaximum());
    minH = PureCore::getRandom(minHSS->getMinimum(), minHSS->getMaximum());
    maxW = PureCore::getRandom(maxWSS->getMinimum(), maxWSS->getMaximum());
    minW = PureCore::getRandom(minWSS->getMinimum(), minWSS->getMaximum());

    minOffsetW = PureCore::getRandom(offsetWmnSS->getMinimum(), offsetWmnSS->getMaximum());
    maxOffsetW = PureCore::getRandom(offsetWmxSS->getMinimum(), offsetWmxSS->getMaximum());
    minOffsetH = PureCore::getRandom(offsetHmnSS->getMinimum(), offsetHmnSS->getMaximum());
    maxOffsetH = PureCore::getRandom(offsetHmxSS->getMinimum(), offsetHmxSS->getMaximum());

    repeatMin = PureCore::getRandom(minRptSS->getMinimum(), minRptSS->getMaximum());
    repeatMax = PureCore::getRandom(maxRptSS->getMinimum(), maxRptSS->getMaximum());
    numberMin = PureCore::getRandom(minNbSS->getMinimum(), minNbSS->getMaximum());
    numberMax = PureCore::getRandom(maxNbSS->getMinimum(), maxNbSS->getMaximum());


    updateUI();
}


void RetriggerWidget::onMinHModified(double v)
{
    minH = v;
    maxHSS->setMinimum(v);
}

void RetriggerWidget::onMaxHModified(double v)
{
    maxH = v;
    minHSS->setMaximum(v);
}

void RetriggerWidget::onMinWModified(double v)
{
    minW = v;
    maxWSS->setMinimum(v);
}

void RetriggerWidget::onMaxWModified(double v)
{
    maxW = v;
    minWSS->setMaximum(v);
}


//offset

void RetriggerWidget::onMinOffsetWModified(double v)
{
    minOffsetW = v;
    offsetWmxSS->setMinimum(v);
}

void RetriggerWidget::onMaxOffsetWModified(double v)
{
    maxOffsetW = v;
    offsetWmnSS->setMaximum(v);
}

void RetriggerWidget::onMinOffsetHModified(double v)
{
    minOffsetH = v;
    offsetHmxSS->setMinimum(v);
}

void RetriggerWidget::onMaxOffsetHModified(double v)
{
    maxOffsetH = v;
    offsetHmnSS->setMaximum(v);
}

//rpt

void RetriggerWidget::onRepeatMinModified(double v)
{
    repeatMin = v;
    maxRptSS->setMinimum(v);
}

void RetriggerWidget::onRepeatMaxModified(double v)
{
    repeatMax = v;
    minRptSS->setMaximum(v);
}

//nb
void RetriggerWidget::onNumberMinModified(double v)
{
    numberMin = v;
    maxNbSS->setMinimum(v);
}

void RetriggerWidget::onNumberMaxModified(double v)
{
    numberMax = v;
    minNbSS->setMaximum(v);
}
