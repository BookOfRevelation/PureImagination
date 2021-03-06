#ifndef PUREEFFECT_H
#define PUREEFFECT_H

#include <QWidget>
#include <QPushButton>

#include "purecore.h"
#include "datawidget.h"

class PureEffect : public QObject
{
    Q_OBJECT
signals:

    void endEffect(bool success);
    void makeProgress(int cur, int max);

public:
    PureEffect(const QString& n);
    virtual ~PureEffect();

    virtual bool init() = 0;
    virtual void process() = 0;
    virtual QWidget* getInfoWidget();
    virtual DataWidget* getDataWidget();
    virtual QWidget* getParamWidget();

    virtual void setParameters(QVector<QVariant> p) = 0;
    virtual QVector<QVariant> getParameters() const = 0;

    virtual PureCore::PureType getOutputType() = 0;
    virtual PureCore::PureType getInputType() = 0;

    virtual PureCore::PureNature getNature() = 0;

    virtual QPair<QString, QString> getInfo() = 0;

    virtual PureEffect* clone() = 0;

    bool binded;

    QString name;

};

#endif // PUREEFFECT_H
