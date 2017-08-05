#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

class DataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataWidget(QWidget *parent = 0);

    virtual bool isBinded() const = 0;

signals:

    void onSend();

public slots:

    void sendData();
};

#endif // DATAWIDGET_H
