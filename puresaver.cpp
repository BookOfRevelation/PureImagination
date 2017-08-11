#include "puresaver.h"

PureSaver::PureSaver(const QString &n)
    : PureEffect(n)
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
