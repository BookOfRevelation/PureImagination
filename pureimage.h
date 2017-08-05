#ifndef PUREIMAGE_H
#define PUREIMAGE_H
#include "puredata.h"
#include <QImage>
class PureImage : public PureData
{
public:
    PureImage();

    int getImageCount() const;
    QImage& getImage(int i);
    QString getName(int i) const;


    void addImage(QImage img, const QString& name);

    void clear();



private:

    QVector<QPair<QImage, QString>> images;

};

#endif // PUREIMAGE_H
