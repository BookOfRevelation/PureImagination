#ifndef HELPZONE_H
#define HELPZONE_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class HelpZone : public QWidget
{
    Q_OBJECT
public:
    explicit HelpZone(QWidget *parent = 0);

    void setWidget(const QString& t, const QString& d);

signals:

public slots:

private:
    QWidget* widget;
    QLabel* ttl;
    QLabel* desc;
    QBoxLayout* mainLt;

};

#endif // HELPZONE_H
