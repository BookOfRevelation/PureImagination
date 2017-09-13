#ifndef FRAGMENTTOIMAGE_H
#define FRAGMENTTOIMAGE_H
#include <QString>
#include <QVector>
#include <QVariant>
#include <QDialog>
#include "puretransformater.h"

class FragmentToImage : public PureTransformater
{
public:
    FragmentToImage(const QString& n);
    ~FragmentToImage();

    bool init();
    void process();

    PureEffect* clone()
    {
        FragmentToImage* e = new FragmentToImage(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Fragment to image",
                    "Refragmente les images."
                    );
    }

};

#endif // FRAGMENTTOIMAGE_H
