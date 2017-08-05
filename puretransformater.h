#ifndef PURETRANSFORMATER_H
#define PURETRANSFORMATER_H

#include "pureeffect.h"

class PureTransformater : public PureEffect
{
public:
    PureTransformater();

    virtual PureCore::PureNature getNature();
};

#endif // PURETRANSFORMATER_H
