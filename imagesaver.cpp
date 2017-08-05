#include "imagesaver.h"
#include "pureimage.h"
#include <QFileDialog>
#include <QDebug>

ImageSaver::ImageSaver()
{
    targetPath = "";
}

PureCore::PureType ImageSaver::getInputType()
{
    return PureCore::Image;
}

bool ImageSaver::init()
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

void ImageSaver::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);

    for(int i = 0 ; i < data->getImageCount() ; ++i)
    {
        QImage img = data->getImage(i);
        QString name = data->getName(i);
        QString fname = targetPath+QString("/")+name;

        img.save(fname);

    }
}
