#include "puresaver.h"

PureSaver::PureSaver()
    : PureEffect()
{

}

PureCore::PureNature PureSaver::getNature()
{
    return PureCore::Saver;
}


PureCore::PureType PureSaver::getOutputType()
{
    return PureCore::NoType;
}
