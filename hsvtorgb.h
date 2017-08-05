#ifndef HSVTORGB_H
#define HSVTORGB_H

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"


class HsvToRgb : public PureFilter
{
public:
    HsvToRgb();
    virtual ~HsvToRgb();

    bool init();

    void process();

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet HsvToRgb",
                    "Cet effet projette chaque triplet\n"
                    "HSV de l'image sur l'échelle RVB."
                    );
    }

private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;
};

#endif // HSVTORGB_H
