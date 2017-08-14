#include "commandparameters.h"

CommandParameters::CommandParameters()
{
    parameters.clear();
    scene =  nullptr;
    effect = currentEffect = nullptr;
}

CommandParameters::~CommandParameters()
{
    if(effect)
    {
        delete effect;
    }
}
