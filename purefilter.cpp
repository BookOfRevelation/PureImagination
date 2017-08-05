#include "purefilter.h"

PureFilter::PureFilter()
    : PureEffect()
{

}


PureCore::PureNature PureFilter::getNature()
{
    return PureCore::Filter;
}
