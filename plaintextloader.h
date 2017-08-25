#ifndef PLAINTEXTLOADER_H
#define PLAINTEXTLOADER_H
#include "pureloader.h"
#include <QVector>
#include <QPair>
#include <QImage>
#include <QVariant>

class PlainTextLoader : public PureLoader
{
public:
    PlainTextLoader(const QString& n);

    PureCore::PureType getOutputType();

    bool init();
    void process();

    PureEffect* clone()
    {
        PlainTextLoader* e = new PlainTextLoader(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Loader Texte",
                    "Charge un fichier texte \n"
                    "du disque dur dans la chaine\n"
                    "de traitement."
                    );
    }

private:
    QString textPath;
};

#endif // PLAINTEXTLOADER_H
