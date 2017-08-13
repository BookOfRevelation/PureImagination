#ifndef GIFSAVER_H
#define GIFSAVER_H
#include "puresaver.h"
#include <QVariant>

class GifSaver : public PureSaver
{
public:
    GifSaver(const QString &n);

    PureCore::PureType getInputType();

    bool init();
    void process();

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Saver Gif",
                    "Enregistre le résultat d'une chaîne\n"
                    "de traitement sous la forme d'un\n"
                    "gif animé dans un dossier\n"
                    "du disque dur."
                    );
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

private:
    QString targetPath;
};

#endif // GIFSAVER_H
