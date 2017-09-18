#ifndef XYZSAVER_H
#define XYZSAVER_H

#include "puresaver.h"
#include <QFileDialog>
#include <QVector>
#include <QVariant>

class XYZSaver : public PureSaver
{
public:
    XYZSaver(const QString& n);
    PureCore::PureType getInputType()
    {
        return PureCore::XYZ;
    }

    bool init();
    void process();

    PureEffect* clone()
    {
        XYZSaver* e = new XYZSaver(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p)
    {
        path = p[0].toString();
    }

    QVector<QVariant> getParameters() const
    {
        QVector<QVariant> r;
        r.clear();

        r.push_back(QVariant(path));
        return r;
    }
    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Saver XYZ",
                    "Enregistre le résultat d'une chaîne\n"
                    "de traitement sous la forme d'un\n"
                    "nuage de point dans un dossier\n"
                    "du disque dur."
                    );
    }

private:

    QString path;
};

#endif // XYZSAVER_H
