#ifndef PURECONDITION_H
#define PURECONDITION_H

#include <QVector>
#include <QImage>
#include "pureimage.h"
#include "purecore.h"

class PureCondition
{
public:
    PureCondition();
    virtual ~PureCondition();
    void init();

    bool checkPixel(int n, int x, int y);
    virtual bool addPixel(const QImage& ref, int x, int y) = 0;


private:

    QVector<QVector<QVector<bool> > > checkTable;

};

class EvenCondition : public PureCondition
{
public:
    EvenCondition();

    bool addPixel(const QImage& ref, int x, int y);
};

class ThresholdCondition : public PureCondition
{
public:

    ThresholdCondition(int t, bool low);

    bool addPixel(const QImage &ref, int x, int y);

private:

    int threshold;
    bool isLow;
};

class PaintCondition : public PureCondition
{
public:
    PaintCondition(QVector<QVector<bool>> px);

    bool addPixel(const QImage &ref, int x, int y) override;

    QVector<QVector<bool>> pixels;

};

#endif // PURECONDITION_H
