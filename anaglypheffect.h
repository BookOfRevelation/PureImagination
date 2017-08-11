#ifndef ANAGLYPHEFFECT_H
#define ANAGLYPHEFFECT_H

#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"



class AnaglyphEffect;
class AnaglyphWidget : public QDialog
{
    Q_OBJECT
public:
    AnaglyphWidget();

//PARAMETERS
    int rx;
    int ry;

    int gx;
    int gy;

    int bx;
    int by;

public slots:
    void onRX(double v);
    void onRY(double v);
    void onGX(double v);
    void onGY(double v);
    void onBX(double v);
    void onBY(double v);


private:
    SlideSpiner* rxSS;
    SlideSpiner* rySS;
    SlideSpiner* gxSS;
    SlideSpiner* gySS;
    SlideSpiner* bxSS;
    SlideSpiner* bySS;


    QPushButton* processBtn;

};



class AnaglyphEffect : public PureFilter
{
public:
    AnaglyphEffect(const QString& n);
    virtual ~AnaglyphEffect();

    bool init();

    void process();

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}


    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Effet Anaglyphe",
                    "Applique un effet anaglyphe sur une\n"
                    "séquence d'image, en décallant les\n"
                    "matrices r, v et b séparément.\n"
                    );
    }


private:
    AnaglyphWidget* gemwidget;



};

#endif // ANAGLYPHEFFECT_H
