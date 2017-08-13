#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include "pureloader.h"
#include <QVector>
#include <QPair>
#include <QImage>
#include <QVariant>

class ImageLoader : public PureLoader
{
public:
    ImageLoader(const QString &n);

    PureCore::PureType getOutputType();

    bool init();
    void process();

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Loader Image",
                    "Loader permettant d'injecter\n"
                    "dans la chaîne de traitement\n"
                    "une séquence d'images présente\n"
                    "sur le disque dur."
                    );
    }

private:
    QStringList filePaths;
};

#endif // IMAGELOADER_H
