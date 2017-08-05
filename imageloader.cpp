#include "imageloader.h"
#include <QFileDialog>
#include "pureimage.h"
#include <QDebug>

ImageLoader::ImageLoader()
    : PureLoader()
{
    filePaths.clear();
}


PureCore::PureType ImageLoader::getOutputType()
{
    return PureCore::Image;

}


bool ImageLoader::init()
{
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png)");
    if(dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        PureCore::lastOpenDir = dialog.directory().absolutePath();

    }

    return filePaths.size() > 0;
}

void ImageLoader::process()
{
    PureImage* imgs = new PureImage;

    for(int i = 0; i < filePaths.size() ; ++i)
    {
        QString name = filePaths[i];
        QFile f(name);
        QFileInfo fi(f);

        QString fname = fi.fileName();

        imgs->addImage(QImage(name), fname);
    }

    PureCore::currentData = imgs;

}
