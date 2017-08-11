#ifndef PURETRANSFORMATER_H
#define PURETRANSFORMATER_H

#include "pureeffect.h"

class PureTransformater : public PureEffect
{
public:
    PureTransformater(const QString& n);

    virtual PureCore::PureNature getNature();
};

#endif // PURETRANSFORMATER_H
