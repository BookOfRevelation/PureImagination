#include "roidialog.h"
#include <QBoxLayout>

ROIDialog::ROIDialog(QPair<int, int> maxDim, QPair<int, int> minDim)
    : QDialog()
{
    xslider = new QSlider(Qt::Horizontal);
    yslider = new QSlider(Qt::Vertical);

    wslider = new QSlider(Qt::Horizontal);
    hslider = new QSlider(Qt::Vertical);

    xslider->setRange(0, maxDim.first - minDim.first);
    yslider->setRange(0, maxDim.second - minDim.second);
    wslider->setRange(minDim.first, maxDim.second);
    hslider->setRange(minDim.second, maxDim.second);

    centralInfo = new QLabel();


    xslider->setValue(0);
    yslider->setValue(0);
    wslider->setValue(wslider->maximum());
    hslider->setValue(hslider->maximum());

    x = y = 0;
    w = wslider->value();
    h = hslider->value();

    connect(xslider, &QSlider::valueChanged, this, [this, maxDim](int value)
    {
        x = value;
        wslider->setMaximum(maxDim.first - x);

        updateLabel();
    });

    connect(yslider, &QSlider::valueChanged, this, [this, maxDim](int value)
    {
        y = value;
        hslider->setMaximum(maxDim.second - y);
        updateLabel();
    });

    connect(wslider, &QSlider::valueChanged, this, [this](int value)
    {
        w = value;
        updateLabel();
    });

    connect(hslider, &QSlider::valueChanged, this, [this](int value)
    {
        h = value;
        updateLabel();
    });


    updateLabel();


    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setLayout(mainLt);
    mainLt->addWidget(new QLabel("x0"));
    mainLt->addWidget(xslider);

    QBoxLayout* mid = new QBoxLayout(QBoxLayout::LeftToRight);
    mid->addWidget(new QLabel("y0"));
    mid->addWidget(yslider);
    mid->addWidget(centralInfo);
    mid->addWidget(hslider);
    mid->addWidget(new QLabel(tr("height")));

    mainLt->addLayout(mid);
    mainLt->addWidget(wslider);
    mainLt->addWidget(new QLabel(tr("width")));


}


int ROIDialog::getX()
{
    return x;
}
int ROIDialog::getY()
{
    return y;
}
int ROIDialog::getW()
{
    return w;
}
int ROIDialog::getH()
{
    return h;
}

void ROIDialog::updateLabel()
{
    centralInfo->setText(
                QString("x0 : %1\ny0 : %2\nwidth : %3 \nheight : %4 ")
                .arg(getX())
                .arg(getY())
                .arg(getW())
                .arg(getH())
                );
}
