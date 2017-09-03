#ifndef GEMPUZZLEEFFECT_H
#define GEMPUZZLEEFFECT_H

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include "multiimagetodir.h"

class GemPuzzleEffect;
class GemWidget : public QDialog
{
    Q_OBJECT
public:
    GemWidget();
    void randomize();


    void updateUI()
    {
        maxHSS->setMaximum(99);
        minHSS->setMinimum(0);

        maxWSS->setMaximum(99);
        minWSS->setMinimum(0);

        maxHSS->setValue(maxH);
        minHSS->setValue(minH);
        maxWSS->setValue(maxW);
        minWSS->setValue(minW);

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

    SlideSpiner* minHSS;
    SlideSpiner* maxHSS;
    SlideSpiner* minWSS;
    SlideSpiner* maxWSS;


    QPushButton* processBtn;

};



class GemPuzzleEffect : public PureFilter
{
public:
    GemPuzzleEffect(const QString &n);
    virtual ~GemPuzzleEffect();

    bool init();

    void process();

    PureEffect* clone()
    {
        GemPuzzleEffect* e = new GemPuzzleEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();
    DataWidget* getDataWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}


    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Effet GemPuzzle",
                    "GemPuzzle est un filtre qui permet\n"
                    "d'appliquer à une séquence d'image\n"
                    "un découpage aléatoire en carrés, pour\n"
                    "immiter le rendu d'un puzzle appelé\n"
                    "Taquin.\n"
                    "Les différents paramètres permettent\n"
                    "de délimiter les dimensions minimum et\n"
                    "maximum des zones de l'image à mélanger."
                    );
    }


private:


    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;

    GemWidget* gemwidget;
    MultiImageToDir* dataW;



};


#endif // GEMPUZZLEEFFECT_H
