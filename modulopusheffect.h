#ifndef MODULOPUSHEFFECT_H
#define MODULOPUSHEFFECT_H



#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"

#include "multiimagetodir.h"
class ModuloPushEffect;
class ModuloPushWidget : public QDialog
{
    Q_OBJECT
public:
    ModuloPushWidget(ModuloPushEffect* effect);

    void updateUI()
    {
        minHSS->setValue(minH);
        maxHSS->setValue(maxH);
        minWSS->setValue(minW);
        maxWSS->setValue(maxW);
    }

//PARAMETERS
    int minH;
    int maxH;

    int minW;
    int maxW;

public slots:
    void onMinHModified(double v);
    void onMaxHModified(double v);
    void onMinWModified(double v);
    void onMaxWModified(double v);


private:
    ModuloPushEffect* burgle;

    SlideSpiner* minHSS;
    SlideSpiner* maxHSS;
    SlideSpiner* minWSS;
    SlideSpiner* maxWSS;


    QPushButton* processBtn;

};



class ModuloPushEffect : public PureFilter
{
public:
    ModuloPushEffect(const QString &n);
    virtual ~ModuloPushEffect();

    bool init();

    void process();

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();
    DataWidget* getDataWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet ModuloPush",
                    "L'effet ModuloPush déplace aléatoirement\n"
                    "des bandes horizontales de l'image. Les\n"
                    "paramètres permettent de faire varier\n"
                    "la largeur des bandes et leurs décallages."
                    );
    }

private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;

    ModuloPushWidget* gemwidget;
    MultiImageToDir* dataW;


};



#endif // MODULOPUSHEFFECT_H
