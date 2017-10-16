#ifndef REINTERPRETEFFECT_H
#define REINTERPRETEFFECT_H
#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"


class ReinterpretEffect : public PureFilter
{
public:
    ReinterpretEffect(const QString &n);
    bool init();
    void process();

    PureEffect* clone()
    {
        ReinterpretEffect* e = new ReinterpretEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }


    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet Reinterpret",
                    ""
                    );
    }

};

#endif // REINTERPRETEFFECT_H
