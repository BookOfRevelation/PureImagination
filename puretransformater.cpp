#include "puretransformater.h"

PureTransformater::PureTransformater()
    : PureEffect()
{

}


PureCore::PureNature PureTransformater::getNature()
{
    return PureCore::Transformater;
}
