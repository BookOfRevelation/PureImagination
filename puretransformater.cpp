#include "puretransformater.h"

PureTransformater::PureTransformater(const QString &n)
    : PureEffect(n)
{

}


PureCore::PureNature PureTransformater::getNature()
{
    return PureCore::Transformater;
}
