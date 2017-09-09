#include "scrollereffect.h"
#include <QLayout>
#include "pureimage.h"
#include <QDebug>

ScrollerWidget::ScrollerWidget()
    : QDialog()
{
    percentH = 0;
    percentV = 0;
    duration = 1;


    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setLayout(mainLt);
    this->setWindowTitle("params");

    percentVSS = new SlideSpiner("Vertical scrolling", "%", 1, 0, 100);
    percentHSS = new SlideSpiner("Horizontal scrolling", "%", 1, 0, 100);
    durationSS = new SlideSpiner("Frame duration", "frame", 1, 1, 60);

    mainLt->addWidget(percentVSS);
    mainLt->addWidget(percentHSS);
    mainLt->addWidget(durationSS);

    process = new QPushButton("Ok");

    QPushButton* randomizebtn = new QPushButton("Randomize");
    mainLt->addWidget(randomizebtn);
    connect(randomizebtn, &QPushButton::pressed, this, &ScrollerWidget::randomize);
    mainLt->addWidget(process);

    connect(process, &QPushButton::pressed, this, [this]()
    {
       percentV = percentVSS->getValue();
       percentH = percentHSS->getValue();
       duration = durationSS->getValue();
       this->accept();
    });



}

void ScrollerWidget::randomize()
{
    percentV = (PureCore::getRandom(0,100));
    percentH = (PureCore::getRandom(0,100));
    duration = (PureCore::getRandom(1,60));

    updateUI();
}

ScrollerEffect::ScrollerEffect(const QString& n)
    : PureFilter(n)
{
    widget = new ScrollerWidget;
}

ScrollerEffect::~ScrollerEffect()
{
    delete widget;
}

bool ScrollerEffect::init()
{
    return widget->exec() == QDialog::Accepted;
}

void ScrollerEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    const int dataSize = data->getImageCount();

    for(int nbimg = 0 ; nbimg < dataSize ; nbimg++)
    {
        QVector<QImage> newImgs;
        newImgs.clear();
        //image de base
        QImage& img = data->getImage(nbimg);
        float vratio = static_cast<float>(widget->percentV)/100.0f;
        int nbv = img.width() * vratio;
        int decalV = 0;
        if(nbv > 0)
        {
            decalV = (img.width()/nbv);
        }

        float hratio = static_cast<float>(widget->percentH)/100.0f;
        int hbv  = img.height() * hratio;
        int decalH = 0;
        if(hbv > 0)
        {
            decalH = (img.height()/hbv);
        }

        bool vfirst = nbv > hbv;

        if(vfirst)
        {
            for(int i = 0 ; i < nbv ; ++i)
            {

                QImage glitched = img.copy();
                for(int x = 0 ; x < glitched.width() ; ++x)
                {
                    for(int y = 0 ; y < glitched.height() ; ++y)
                    {
                        glitched.setPixel(x, y, img.pixel((x+decalV*(i+1))%img.width(), (y+decalH*(i+1))%img.height()));
                    }
                }
                newImgs.push_back(glitched);


            }
        }
        else
        {
            for(int i = 0 ; i < hbv ; ++i)
            {

                QImage glitched = img.copy();
                for(int x = 0 ; x < glitched.width() ; ++x)
                {
                    for(int y = 0 ; y < glitched.height() ; ++y)
                    {
                        glitched.setPixel(x, y, img.pixel((x+decalV*(i+1))%img.width(), (y+decalH*(i+1))%img.height()));
                    }
                }
                newImgs.push_back(glitched);
            }
        }

        int cx = 0;
        for(int i = 0 ; i < newImgs.size() ; ++i)
        {

            for(int fps = 0 ; fps < widget->duration ; ++fps)
            {
                QString name = data->getName(nbimg).split(".")[0] + QString::number(cx++);
                data->addImage(newImgs[i], name);
            }
        }

    }

}


QVector<QVariant> ScrollerEffect::getParameters() const
{
    QVector<QVariant> res;

    res.push_back(QVariant(widget->percentV));
    res.push_back(QVariant(widget->percentH));
    res.push_back(QVariant(widget->duration));
    return res;
}

void ScrollerEffect::setParameters(QVector<QVariant> p)
{
    widget->percentV = p[0].toInt();
    widget->percentH = p[1].toInt();
    widget->duration = p[2].toInt();
    widget->updateUI();
}


QWidget* ScrollerEffect::getParamWidget()
{
    return this->widget;
}
