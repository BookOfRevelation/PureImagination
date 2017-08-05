#ifndef MELTEFFECT_H
#define MELTEFFECT_H


#include <QString>
#include <QPair>
#include <QImage>
#include "purefilter.h"
class MeltEffect : public PureFilter
{
public:
    MeltEffect();
    bool init();

    void process();

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
    QVector<QImage> baseImages;

    QImage melting;

};

#endif // MELTEFFECT_H
