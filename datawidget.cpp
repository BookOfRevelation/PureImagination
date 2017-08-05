#include "datawidget.h"

DataWidget::DataWidget(QWidget *parent) : QWidget(parent)
{

}


void DataWidget::sendData()
{
    emit onSend();
}
