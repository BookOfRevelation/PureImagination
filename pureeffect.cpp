#include "pureeffect.h"

PureEffect::PureEffect(const QString& n)
    : QObject()
{
    binded = false;
    name = n;
}

PureEffect::~PureEffect()
{

}

QWidget* PureEffect::getInfoWidget()
{
    return nullptr;
}
DataWidget *PureEffect::getDataWidget()
{
    return nullptr;
}

QWidget* PureEffect::getParamWidget()
{
    return nullptr;
}

