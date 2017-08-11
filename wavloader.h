#ifndef WAVLOADER_H
#define WAVLOADER_H
#include "pureloader.h"
#include <QPair>
#include <aquila/global.h>
#include <aquila/source/WaveFile.h>



class WavLoader : public PureLoader
{
public:
    WavLoader(const QString &n);

    PureCore::PureType getOutputType()
    {
        return PureCore::Wave;
    }

    bool init();
    void process();

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Loader Wave",
                    "Charge un fichier son "
                    "(.wav) depuis l'ordinnateur."
                    );
    }

private:

    QString filePath;
};

#endif // WAVLOADER_H
