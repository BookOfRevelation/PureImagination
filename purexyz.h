#ifndef PUREXYZ_H
#define PUREXYZ_H
#include "puredata.h"
#include <QVector>
#include <QString>
#include <QVector3D>

class PureXYZ : public PureData
{
public:
    PureXYZ();

    void addPoint(int x, int y, int z);

    QVector3D getPoint(int i);

    int count() const
    {
        return points.count();
    }


    void clear()
    {
        points.clear();
        w = 0;
        h = 0;
    }

    int width() const
    {
        return w;
    }

    int height() const
    {
        return h;
    }

private:

    QVector<QVector3D> points;

    int w;
    int h;
};

#endif // PUREXYZ_H
