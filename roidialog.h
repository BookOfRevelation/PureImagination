#ifndef ROIDIALOG_H
#define ROIDIALOG_H

#include <QDialog>
#include <QPair>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class ROIDialog : public QDialog
{
    Q_OBJECT

public:
    ROIDialog(QPair<int, int> maxDim, QPair<int, int> minDim);

    int getX();
    int getY();
    int getW();
    int getH();

public slots:

    void updateLabel();

private:
    int x;
    int y;
    int w;
    int h;

    QSlider* xslider;
    QSlider* yslider;
    QSlider* wslider;
    QSlider* hslider;

    QLabel* centralInfo;
};

#endif // ROIDIALOG_H
