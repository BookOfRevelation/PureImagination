#include "pureloader.h"

PureLoader::PureLoader()
    : PureEffect()
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
