#include "tanglefusioneffect.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>

TangleFusionEffect::TangleFusionEffect(const QString &n)
    : PureFilter(n),fileName("")
{

}

bool TangleFusionEffect::init()
{
    bool result = false;

    baseImages.clear();

    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png)");
    QStringList fileNames;
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        QString path;
        foreach (path, fileNames)
        {

            PureCore::lastOpenDir = QFileInfo(path).absoluteDir().absolutePath();
            baseImages.push_back(QImage(path));
        }

        fileName = QFileDialog::getSaveFileName(nullptr,
                                                "Save File",
                                                PureCore::lastTargetDir,
                                                "Images (*.png *.xpm *.jpg)");

        result = (fileName != "");
        if(result)
        {
            PureCore::lastTargetDir = QFileInfo(fileName).absoluteDir().absolutePath();
        }
        qDebug()<<fileName;
    }

    return result;
}


void TangleFusionEffect::process()
{
    QImage ref = baseImages[0];
    for(int i = 1 ; i < baseImages.size() ; i++)
    {
        QImage img = baseImages[i];

        img = img.scaled(ref.width(), ref.height());

        baseImages[i] = img;
    }


    int occurences = 0;
    int maxoccur = ref.height()*ref.width();
    QImage newImage(ref.width(), ref.height(), ref.format());
    for(int w = 0 ; w < ref.height() ; ++w)
    {
        QImage img = baseImages[w%baseImages.size()];
        for(int h = 0 ; h < ref.width() ; ++h)
        {
           newImage.setPixelColor(h,w, img.pixelColor(h,w));
           emit makeProgress(occurences++, maxoccur);

        }
    }

    emit endEffect(newImage.save(fileName));
}
