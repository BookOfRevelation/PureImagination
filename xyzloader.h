#ifndef XYZLOADER_H
#define XYZLOADER_H
#include "pureloader.h"
#include "purexyz.h"

class XYZLoader : public PureLoader
{
public:
    XYZLoader(const QString& n);

    PureCore::PureType getOutputType()
    {
        return PureCore::XYZ;
    }

    bool init();
    void process();

    PureEffect* clone()
    {
        XYZLoader* e = new XYZLoader(this->name);
        e->setParameters(this->getParameters());
        return e;
    }


    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Loader XYZ",
                    "Loader permettant d'injecter\n"
                    "dans la chaîne de traitement\n"
                    "une séquence d'images présente\n"
                    "sur le disque dur."
                    );
    }

private:

    QString filePath;

};

#endif // XYZLOADER_H
