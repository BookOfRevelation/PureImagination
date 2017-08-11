#ifndef PURELOADER_H
#define PURELOADER_H

#include "pureeffect.h"

class PureLoader : public PureEffect
{
public:
    PureLoader(const QString& n);

    virtual PureCore::PureNature getNature();

    virtual PureCore::PureType getInputType();
};

#endif // PURELOADER_H
