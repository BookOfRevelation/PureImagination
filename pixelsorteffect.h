#ifndef PIXELSORTEFFECT_H
#define PIXELSORTEFFECT_H

#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include <QDialog>
#include <QComboBox>

class PixelSortWidget : public QDialog
{
public:
    PixelSortWidget();
    void randomize();
    void updateUI()
    {
      typeCB->setCurrentText(sortingType);
      shapeCB->setCurrentText(sortingShape);
    }

    //parameters
    QString sortingType;
    QString sortingShape;

private:
    QComboBox* typeCB;
    QComboBox* shapeCB;

    QPushButton* processBtn;
    QPushButton* randomBtn;
};

class PixelSortEffect : public PureFilter
{
public:
    PixelSortEffect(const QString& n);
    virtual ~PixelSortEffect();

    bool init();
    void process();

    PureEffect* clone()
    {
        PixelSortEffect* e = new PixelSortEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return QPair<QString, QString>(
                    "Effet Pixel Sorting",
                   ""
                    );
    }

private:
    PixelSortWidget* widget;
};

#endif // PIXELSORTEFFECT_H
