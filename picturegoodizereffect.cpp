#include "picturegoodizereffect.h"
#include "pureimage.h"

#include <QBoxLayout>
#include <QDebug>

PictureGoodizerEffect::PictureGoodizerEffect(const QString& n)
    : PureFilter(n)
{
    widget = new PictureGoodizerWidget();
}

PictureGoodizerEffect::~PictureGoodizerEffect()
{
    delete widget;
}

bool PictureGoodizerEffect::init()
{
    return (widget->exec() == QDialog::Accepted);
}

void PictureGoodizerEffect::process()
{
    int power = widget->power;
    float velocity = widget->velocity;

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    QImage& img = data->getImage(0);
    const int width = img.width();
    const int height = img.height();

    QMap<int, QVector<QPoint>> pixels;
    pixels.clear();

    for(int i = 0 ; i < width ; ++i)
    {
        for(int j = 0 ; j < height ; ++j)
        {
            QColor c = img.pixelColor(i, j);
            int key = c.value();
            if(pixels.keys().contains(key))
            {
                pixels[key].push_back(QPoint(i, j));
            }
            else
            {
                QVector<QPoint> p;
                p.clear();
                p.push_back(QPoint(i, j));
                pixels.insert(key, p);
            }
        }
    }

    int totalPx = width * height;

    //how many low and high px we have to take
    const int nbPx = ((static_cast<float>(totalPx)*static_cast<float>(power))/100.0f)/2;
    qDebug()<<"nb px : "<<totalPx;
    qDebug()<<"percent : "<<nbPx;
    int cx = 0;
    //find the lowest pixels
    auto keys = pixels.keys();
    for(int i = 0 ; i < keys.count() && cx < nbPx; ++i)
    {
        QVector<QPoint> pixel = pixels[keys[i]];
        for(int j = 0 ; j < pixel.count() && cx < nbPx ; ++j)
        {

            QColor c = img.pixelColor(pixel.at(j)).toHsv();

            int saturation = static_cast<float>(c.saturation()) * velocity;
            if(saturation > 255)
            {
                saturation = 255;
            }
            int value = static_cast<float>(c.value())*velocity;
            if(value > 255)
            {
                value = 255;
            }
            c.setHsv(c.hue(),
                     saturation,
                     value);
            img.setPixelColor(pixel.at(j), c);
            ++cx;
        }
    }

    cx = 0;
    //find the highest pixels
    for(int i = keys.count() -1 ; i >= 0 && cx < nbPx ; --i)
    {
        QVector<QPoint> pixel = pixels[keys[i]];
        for(int j = 0 ; j < pixel.count() && cx < nbPx ; ++j)
        {
            QColor c = img.pixelColor(pixel.at(j)).toHsv();
            int saturation = static_cast<float>(c.saturation()) * velocity;
            if(saturation > 255)
            {
                saturation = 255;
            }
            int value = static_cast<float>(c.value())*velocity;
            if(value > 255)
            {
                value = 255;
            }
            c.setHsv(c.hue(),
                     saturation,
                     value);
            img.setPixelColor(pixel.at(j), c);
            ++cx;
        }
    }

}

QWidget* PictureGoodizerEffect::getParamWidget()
{
    return widget;
}

QVector<QVariant> PictureGoodizerEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(widget->power);
    res.push_back(widget->velocity);

    return res;
}

void PictureGoodizerEffect::setParameters(QVector<QVariant> p)
{
    widget->power = p[0].toInt();
    widget->velocity = p[1].toFloat();

    widget->updateUI();
}

PictureGoodizerWidget::PictureGoodizerWidget()
{
    power = 1;
    velocity = 1.0f;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    powerSS = new SlideSpiner("Power : ", "%", 1, 1, 50);
    veloSS = new SlideSpiner("Velocity : ", "%",3, 1.0f, 3.0f);
    processBtn = new QPushButton("Ok");

    mainLt->addWidget(powerSS);
    mainLt->addWidget(veloSS);

    randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &PictureGoodizerWidget::randomize);

    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(powerSS, &SlideSpiner::valueChanged, this, [this](float v)
    {
        power = v;
    });

    connect(veloSS, &SlideSpiner::valueChanged, this, [this](float v)
    {
        velocity = v;
    });
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);

}

void PictureGoodizerWidget::randomize()
{
    power = PureCore::getRandom(powerSS->getMinimum(), powerSS->getMaximum());
    velocity = PureCore::getRandom(veloSS->getMinimum(), veloSS->getMaximum());

    updateUI();
}
