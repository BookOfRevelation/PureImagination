#ifndef GHOSTFUSIONEFFECT_H
#define GHOSTFUSIONEFFECT_H

#include <QString>
#include <QPair>
#include <QImage>
#include "purefilter.h"
class GhostFusionEffect : public PureFilter
{
public:
    GhostFusionEffect(const QString &n);
    bool init();

    void process();

    PureEffect* clone()
    {
        GhostFusionEffect* e = new GhostFusionEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet GhostFusion",
                    "GhostFusion permet de mélanger une\n"
                    "séquence d'image pour générer une seule\n"
                    "image contenant toutes les images\n"
                    "d'entrées, en calculant la moyenne de\n"
                    "de chaque pixel."
                    );
    }
    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

private:

    QString fileName;
    QVector<QImage> baseImages;

};

#endif // GHOSTFUSIONEFFECT_H
