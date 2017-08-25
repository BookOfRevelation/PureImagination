#ifndef TEXTTOIMG_H
#define TEXTTOIMG_H

#include <QString>
#include <QVector>
#include <QVariant>
#include "puretransformater.h"

class TextToImg : public PureTransformater
{
public:
    TextToImg(const QString &n);
    bool init();
    void process();

    PureEffect* clone()
    {
        TextToImg* e = new TextToImg(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Text ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Text to Img",
                    "Transforme un texte en image."
                    );
    }


};

#endif // TEXTTOIMG_H
