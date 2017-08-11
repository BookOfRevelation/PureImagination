#include "purefilter.h"

PureFilter::PureFilter(const QString& n)
    : PureEffect(n)
{

}


PureCore::PureNature PureFilter::getNature()
{
    return PureCore::Filter;
}
