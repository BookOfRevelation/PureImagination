#ifndef PURESAVER_H
#define PURESAVER_H
#include "pureeffect.h"

class PureSaver : public PureEffect
{
public:
    PureSaver();

    virtual PureCore::PureNature getNature();
    virtual PureCore::PureType getOutputType();
};

#endif // PURESAVER_H
