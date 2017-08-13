#ifndef NOIZIFIEREFFECT_H
#define NOIZIFIEREFFECT_H

#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include <QDialog>

class NoizifierEffect;
class NoizifierWidget : public QDialog
{
    Q_OBJECT
public:
    NoizifierWidget(NoizifierEffect* effect);

    void updateUI()
    {
        rateSS->setValue(rate);
    }

//PARAMETERS
    int rate;
public slots:
    void onRateModified(double v);



private:
    NoizifierEffect* burgle;

    SlideSpiner* rateSS;

    QPushButton* processBtn;

};



class NoizifierEffect  : public PureFilter
{
public:
    NoizifierEffect(const QString &n);
    virtual ~NoizifierEffect();

    bool init();

    void process();

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return QPair<QString, QString>(
                    "Effet Noizifier",
                    "Applique un algorithme de\n"
                    "bruitage aléatoire à une \n"
                    "séquence d'images."
                    );
    }

private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;

    NoizifierWidget* gemwidget;


};


#endif // NOIZIFIEREFFECT_H
