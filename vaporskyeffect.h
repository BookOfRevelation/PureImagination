#ifndef VAPORSKYEFFECT_H
#define VAPORSKYEFFECT_H


#include "purefilter.h"

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>

class VaporSkyEffect;
class VaporSkyWidget : public QWidget
{
    Q_OBJECT
public:
    VaporSkyWidget(VaporSkyEffect* effect);

//PARAMETERS
    int seuil;

public slots:
    void onSeuilModified(double v);


private:
    VaporSkyEffect* burgle;

    SlideSpiner* seuilSS;


    QPushButton* processBtn;

};



class VaporSkyEffect : public PureFilter
{
public:
    VaporSkyEffect(const QString &n);
    virtual ~VaporSkyEffect();

    bool init();

    void process();

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;
    QImage bgimg;

    VaporSkyWidget* gemwidget;


};





#endif // VAPORSKYEFFECT_H
