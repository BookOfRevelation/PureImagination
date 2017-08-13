#include "gifsaver.h"
#include "pureimage.h"
#include <QFileDialog>
#include "gif.h"


GifSaver::GifSaver(const QString &n)
    : PureSaver(n)
{
    targetPath = "";
}


PureCore::PureType GifSaver::getInputType()
{
    return PureCore::Image;
}

bool GifSaver::init()
{
    targetPath = QFileDialog::getExistingDirectory(nullptr, QString("Target Directory"),
                                                   PureCore::lastTargetDir,
                                                   QFileDialog::ShowDirsOnly);
    if(targetPath != "")
    {
        PureCore::lastTargetDir = targetPath;
    }

    return (targetPath != "");
}

void GifSaver::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    QImage firstImage = data->getImage(0);
    GifWriter* w = new GifWriter();
    GifBegin(w, (targetPath + "/gifresult.gif").toStdString().c_str(), firstImage.width(), firstImage.height(), 10, 8);
    GifWriteFrame(w ,firstImage.bits(), firstImage.width(), firstImage.height(),10, 8);
    for(int i = 1 ; i < data->getImageCount() ; ++i)
    {
        QImage curImg = data->getImage(i);
        curImg = curImg.scaled(firstImage.width(), firstImage.height());
        GifWriteFrame(w ,curImg.bits(), curImg.width(), curImg.height(),10,8);
    }
    GifEnd(w);

}

QVector<QVariant> GifSaver::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(targetPath));

    return res;
}

void GifSaver::setParameters(QVector<QVariant> p)
{
    targetPath = p[0].toString();
}
