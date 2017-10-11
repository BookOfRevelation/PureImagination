#include "slidespiner.h"
#include <QtMath>
SlideSpiner::SlideSpiner(const QString& name, const QString& unitName, int precision, double min, double max, QWidget *parent)
    : QWidget(parent)
{
    powFactor = qPow(10.0, precision + 0.0);

    spinBox = new QDoubleSpinBox;
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setDecimals(precision - 1);
    spinBox->setValue(min);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(min * powFactor);
    slider->setMaximum(max * powFactor);
    slider->setValue(min);

    header = new QLabel(name);
    unit = new QLabel(unitName);

    mainLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    this->setLayout(mainLayout);

    mainLayout->addWidget(header);
    mainLayout->addWidget(slider);
    mainLayout->addWidget(spinBox);
    mainLayout->addWidget(unit);

    connect(
                spinBox,
                static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,
                &SlideSpiner::spinToSlide
                );
    connect(slider, &QSlider::valueChanged, this, &SlideSpiner::slideToSpin);


}

double SlideSpiner::getValue() const
{
    return spinBox->value();
}


void SlideSpiner::spinToSlide(double value)
{
    int newValue = value * powFactor;
    slider->setValue(newValue);

    emit valueChanged(value);
}

void SlideSpiner::slideToSpin(int value)
{
    double newValue = (static_cast<double>(value)) / powFactor;
    spinBox->setValue(newValue);

    emit valueChanged(newValue);
}

void SlideSpiner::setToMiddle()
{
    int mean = (slider->minimum() + slider->maximum())/2;
    slider->setValue(mean);
    slideToSpin(mean);
}

void SlideSpiner::setMaximum(double max)
{
    slider->setMaximum(max * powFactor);
    spinBox->setMaximum(max);

    if(spinBox->value() > max)
    {
        spinBox->setValue(max);
        int newValue = max * powFactor;
        slider->setValue(newValue);
    }
}
void SlideSpiner::setMinimum(double min)
{
    slider->setMinimum(min * powFactor);
    spinBox->setMinimum(min);

    if(spinBox->value() < min)
    {
        spinBox->setValue(min);
        int newValue = min * powFactor;
        slider->setValue(newValue);
    }
}

void SlideSpiner::setValue(double val)
{
    spinBox->setValue(val);
    spinToSlide(val);
}
