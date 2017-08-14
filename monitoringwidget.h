#ifndef MONITORINGWIDGET_H
#define MONITORINGWIDGET_H

#include "megamonitoring.h"

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTimer>
#include <QLayout>

class MonitoringWidget : public QWidget
{
    Q_OBJECT
public:
    MonitoringWidget(QWidget *parent = 0);
    ~MonitoringWidget();

    void updateBars();

private:
    QProgressBar* ramBar;
    QTimer* mainTimer;
};

#endif // MONITORINGWIDGET_H
