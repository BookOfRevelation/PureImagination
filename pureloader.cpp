#include "pureloader.h"

PureLoader::PureLoader(const QString & n)
    : PureEffect(n)
{

}

PureCore::PureNature PureLoader::getNature()
{
    return PureCore::Loader;
}

PureCore::PureType PureLoader::getInputType()
{
    return PureCore::NoType;
}
