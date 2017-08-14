#ifndef HSVTORGB_H
#define HSVTORGB_H

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"


class HsvToRgb : public PureFilter
{
public:
    HsvToRgb(const QString &n);
    virtual ~HsvToRgb();

    bool init();

    void process();

    PureEffect* clone()
    {
        HsvToRgb* e = new HsvToRgb(this->name);
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
                    "Effet HsvToRgb",
                    "Cet effet projette chaque triplet\n"
                    "HSV de l'image sur l'échelle RVB."
                    );
    }

};

#endif // HSVTORGB_H
