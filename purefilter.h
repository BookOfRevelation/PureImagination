#ifndef PUREFILTER_H
#define PUREFILTER_H

#include "pureeffect.h"

class PureFilter : public PureEffect
{
public:
    PureFilter();

    virtual PureCore::PureNature getNature();
};


#endif // PUREFILTER_H
