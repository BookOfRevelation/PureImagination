#include "imageloader.h"
#include <QFileDialog>
#include "pureimage.h"
#include <QDebug>

ImageLoader::ImageLoader(const QString &n)
    : PureLoader(n)
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

    if(filePaths.size() > 0)
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

    return filePaths.size() > 0;
}

void ImageLoader::process()
{


}

QVector<QVariant> ImageLoader::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(filePaths));

    return res;
}

void ImageLoader::setParameters(QVector<QVariant> p)
{
   filePaths = p[0].toStringList();
}
