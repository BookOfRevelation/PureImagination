#ifndef COMPOSITIONEFFECT_H
#define COMPOSITIONEFFECT_H

#include "purefilter.h"

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>

class CompositionWidget : public QDialog
{
    Q_OBJECT
public:
    CompositionWidget();

    //PARAMETERS
    int pixelDim;
    QVector<QImage> pixelImages;

public slots:
    void onPixelModified(double v);
    void onImageLoad();

private:
    SlideSpiner* pixelSS;
    QLineEdit* outputLine;
    QPushButton* loadBtn;

    QPushButton* processBtn;


};

class CompositionEffect : public PureFilter
{
public:
    CompositionEffect(const QString &n);

    bool init();

    void process();


    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet Composition",
                    "Assemble les images d'entrées "
                    "pour générer l'image de référence."
                    );
    }

private:

    CompositionWidget* widget;


    QVector<QImage> images;
    QVector<QColor> colors;

    QImage neareastColor(QColor c);


};


#endif // COMPOSITIONEFFECT_H
