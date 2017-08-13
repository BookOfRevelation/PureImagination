#ifndef SUBLIMINALEFFECT_H
#define SUBLIMINALEFFECT_H
#include "purefilter.h"

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QCheckBox>

class SubliminalWidget : public QDialog
{
    Q_OBJECT
public:
    SubliminalWidget();

    void updateUI()
    {
        fsSS->setValue(frameSkip);
        subSS->setValue(subDuration);
        repeatSeq->setChecked(repeat);
    }

//PARAMETERS
    int frameSkip;
    int subDuration;
    bool repeat;
    QVector<QImage> subImages;

public slots:
    void onFrameSkipModified(double v);
    void onSubDurationModified(double v);
    void onImageLoad();

private:
    SlideSpiner* fsSS;
    SlideSpiner* subSS;
    QCheckBox* repeatSeq;

    QLineEdit* outputLine;
    QPushButton* loadBtn;

    QPushButton* processBtn;
};


class SubliminalEffect : public PureFilter
{
public:
    SubliminalEffect(const QString &n);
    bool init();

    void process();

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet Subliminal",
                    "Interlace les images d'une séquence\n "
                    "dans une autre séquence."
                    );
    }

private:

    SubliminalWidget* widget;

    QVector<QImage> subImages;

};

#endif // SUBLIMINALEFFECT_H
