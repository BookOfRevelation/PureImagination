#include "monitoringwidget.h"

MonitoringWidget::MonitoringWidget(QWidget *parent)
    : QWidget(parent)
{
    ramBar = new QProgressBar();
    ramBar->setMinimum(0);
    ramBar->setMaximum(100);;
    ramBar->setValue(0);

    this->setStyleSheet(
                "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                "QProgressBar::chunk {background-color: #33CC33; width: 10px; margin: 0.5px;}"
                );

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setLayout(mainLt);

    QBoxLayout* ramLt = new QBoxLayout(QBoxLayout::LeftToRight);
    ramLt->addWidget(new QLabel(tr("Total RAM usage : ")));
    ramLt->addWidget(ramBar);

    mainLt->addLayout(ramLt);

    mainTimer = new QTimer();
    connect(mainTimer, &QTimer::timeout, this, &MonitoringWidget::updateBars);
    updateBars();


}

MonitoringWidget::~MonitoringWidget()
{
    delete mainTimer;
}


void MonitoringWidget::updateBars()
{
    int percent = static_cast<int>(MegaMonitoring::getUsedPercentRAM());
    ramBar->setValue(percent);

    if(percent < 25)
    {
        this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #33CC33; width: 10px; margin: 0.5px;}"
                    );
    }
    else if(percent < 50)
    {
        this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #CCFF99; width: 10px; margin: 0.5px;}"
                    );
    }
    else if(percent < 75)
    {
        this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #FFFF99; width: 10px; margin: 0.5px;}"
                    );
    }
    else if(percent < 85)
    {
        this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #FF9933; width: 10px; margin: 0.5px;}"
                    );
    }
    else
    {
        this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #FF3300; width: 10px; margin: 0.5px;}"
                    );
    }

    mainTimer->start(2000);
}
