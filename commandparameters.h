#ifndef COMMANDPARAMETERS_H
#define COMMANDPARAMETERS_H

#include "purescene.h"
#include "pureeffect.h"

#include <QVariant>
#include <QVector>


class CommandParameters
{
public:
    CommandParameters();

    PureScene* scene;
    PureEffect* effect;
    PureEffect* currentEffect;

    QVector<QVariant> parameters;


};

#endif // COMMANDPARAMETERS_H
