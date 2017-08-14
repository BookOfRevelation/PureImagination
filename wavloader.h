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

    PureEffect* clone()
    {
        WavLoader* e = new WavLoader(this->name);
        e->setParameters(this->getParameters());
        return e;
    }


    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

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
