#ifndef GIFLOADER_H
#define GIFLOADER_H
#include "pureloader.h"
#include <QVector>
#include <QPair>
#include <QImage>
#include <QVariant>

class GifLoader : public PureLoader
{
public:
    GifLoader(const QString &n);

    PureCore::PureType getOutputType();

    bool init();
    void process();

    QPair<QString, QString> getInfo()
    {
        return  QPair<QString, QString>(
                     "Loader Gif",
                     "Loader permettant d'injecter\n"
                     "dans la chaîne de traitement\n"
                     "un gif animé, transformé en \n"
                     "séquence d'images."
                     );
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

private:

    QString filePath;
};

#endif // GIFLOADER_H
