#ifndef RGBTOHSV_H
#define RGBTOHSV_H

#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"


class RgbToHsv  : public PureFilter
{
public:
    RgbToHsv(const QString &n);
    virtual ~RgbToHsv();

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
                    "Effet RgbToHsv",
                    "Cet effet projette chaque triplet\n"
                    "RVB de l'image sur l'échelle HSV."
                    );
    }


private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;
};



#endif // RGBTOHSV_H
