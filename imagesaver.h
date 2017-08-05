#ifndef IMAGESAVER_H
#define IMAGESAVER_H
#include "puresaver.h"

class ImageSaver : public PureSaver
{
public:
    ImageSaver();

    PureCore::PureType getInputType();

    bool init();
    void process();

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Saver Image",
                    "Enregistre le résultat d'une chaîne\n"
                    "de traitement sous la forme d'une\n"
                    "séquence d'image dans un dossier\n"
                    "du disque dur."
                    );
    }

private:
    QString targetPath;

};

#endif // IMAGESAVER_H
