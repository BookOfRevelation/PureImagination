#ifndef GHOSTFUSIONEFFECT_H
#define GHOSTFUSIONEFFECT_H

#include <QString>
#include <QPair>
#include <QImage>
#include "purefilter.h"
class GhostFusionEffect : public PureFilter
{
public:
    GhostFusionEffect();
    bool init();

    void process();

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

private:

    QString fileName;
    QVector<QImage> baseImages;

};

#endif // GHOSTFUSIONEFFECT_H
