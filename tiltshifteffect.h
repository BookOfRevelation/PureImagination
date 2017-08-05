#ifndef TILTSHIFTEFFECT_H
#define TILTSHIFTEFFECT_H
#include "purefilter.h"

class TiltShiftEffect : public PureFilter
{
public:
    TiltShiftEffect();
    virtual ~TiltShiftEffect();

    bool init();
    void process();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}


    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet TiltShift",
                    "Applique un flou gaussien sur\n"
                    "la partie haute et basse de l'image\n"
                    "pour un effet \"maquette\"."
                    );
    }

private:
};

#endif // TILTSHIFTEFFECT_H
