#ifndef MELTEFFECT_H
#define MELTEFFECT_H


#include <QString>
#include <QPair>
#include <QImage>
#include "purefilter.h"
class MeltEffect : public PureFilter
{
public:
    MeltEffect(const QString &n);
    bool init();

    void process();
    PureEffect* clone()
    {
        MeltEffect* e = new MeltEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet MeltEffect",
                    "Mélange les images sélectionnées "
                    "avec une image cible, en suivant "
                    "les règles de synthèse additive."
                    );
    }

private:

    QString fileName;

    QImage melting;

};

#endif // MELTEFFECT_H
