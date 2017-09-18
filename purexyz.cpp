#include "purexyz.h"

PureXYZ::PureXYZ()
    : PureData()
{
    points.clear();
    w = 0;
    h = 0;
}


void PureXYZ::addPoint(int x, int y, int z)
{
    if(x >= w)
    {
        w = x+1;
    }
    if(y >= h)
    {
        h = y+1;
    }
    points.push_back(QVector3D(x, y, z));
}

QVector3D PureXYZ::getPoint(int i)
{
    return points[i];
}
