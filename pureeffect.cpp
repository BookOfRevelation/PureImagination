#include "pureeffect.h"

PureEffect::PureEffect()
    : QObject()
{
    binded = false;
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

