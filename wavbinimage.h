#ifndef WAVBINIMAGE_H
#define WAVBINIMAGE_H

#include "puretransformater.h"
#include <QPair>
#include <QDialog>
#include "slidespiner.h"
#include <QLayout>
#include <QPushButton>
#include <QVariant>

class WavBinWidget : public QDialog
{
    Q_OBJECT
public:

    WavBinWidget();

    SlideSpiner* sizeSd;
    QPushButton* ok;
    QBoxLayout* mainLt;

    void updateUI()
    {
        sizeSd->setValue(size);
    }

    int size;

public slots:

    void goPressed();

};

class WavBinImage  : public PureTransformater
{
public:
    WavBinImage(const QString &n);
    bool init();

    void process();

    PureEffect* clone()
    {
        WavBinImage* e = new WavBinImage(this->name);
        e->setParameters(this->getParameters());
        return e;
    }



    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Wave ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Wav binary Image",
                    "Transforme un signal audio"
                    "wave en image, en se fondant"
                    "sur la représentation binaire"
                    "du signal."
                    );
    }

private:
    WavBinWidget* w;


};

#endif // WAVBINIMAGE_H
