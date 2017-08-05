#ifndef RETRIGGEREFFECT_H
#define RETRIGGEREFFECT_H
#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"

class RetriggerEffect;

class RetriggerWidget : public QDialog
{
    Q_OBJECT
public:
    RetriggerWidget();

//PARAMETERS
    int minH;
    int maxH;

    int minW;
    int maxW;


    int minOffsetH;
    int maxOffsetH;
    int minOffsetW;
    int maxOffsetW;

    int repeatMin;
    int repeatMax;

    int numberMin;
    int numberMax;

public slots:
    void onMinHModified(double v);
    void onMaxHModified(double v);
    void onMinWModified(double v);
    void onMaxWModified(double v);


    void onMinOffsetHModified(double v);
    void onMaxOffsetHModified(double v);
    void onMinOffsetWModified(double v);
    void onMaxOffsetWModified(double v);

    void onRepeatMinModified(double v);
    void onRepeatMaxModified(double v);

    void onNumberMinModified(double v);
    void onNumberMaxModified(double v);


private:

    SlideSpiner* minHSS;
    SlideSpiner* maxHSS;
    SlideSpiner* minWSS;
    SlideSpiner* maxWSS;


    SlideSpiner* offsetHmnSS;
    SlideSpiner* offsetHmxSS;

    SlideSpiner* offsetWmnSS;
    SlideSpiner* offsetWmxSS;

    SlideSpiner* minRptSS;
    SlideSpiner* maxRptSS;
    SlideSpiner* minNbSS;
    SlideSpiner* maxNbSS;


    QPushButton* processBtn;

};

class RetriggerEffect : public PureFilter
{
public:
    RetriggerEffect();
    virtual ~RetriggerEffect();

    bool init();

    void process();

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet Retrigger",
                    "Cet effet copie/colle des parties\n"
                    "aléatoires de l'image avec un \n"
                    "décallage.\n"
                    "Les paramètres permettent de faire\n"
                    "varier la taille des zones répétées,\n"
                    "ainsi que le nombre de zones et\n"
                    "le nombre de répétitions."
                    );
    }

private:


    RetriggerWidget* gemwidget;


};

#endif // RETRIGGEREFFECT_H
