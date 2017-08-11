#include "imagetoxyz.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include <QDir>
#include <QtMath>

ImageToXYZ::ImageToXYZ(const QString &n)
    : PureTransformater(n),splitFactor(1.05)
{

}


bool ImageToXYZ::init()
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

        targetFile = QFileDialog::getSaveFileName(nullptr, "Save File",
                                                          PureCore::lastTargetDir,
                                                          "Cloud point (*.xyz)");

        result = (targetFile != "");
        if(result)
        {
            QFile f(targetFile);
            QFileInfo fi(f);
            PureCore::lastTargetDir = fi.absoluteDir().absolutePath();
        }
        qDebug()<<targetFile;
    }

    return result;
}


void ImageToXYZ::process()
{
    bool result = true;
    int occurences = 0;
    int maxoccur = 0;
    for(int i = 0 ; i < baseImages.size() ; ++i)
    {
        maxoccur += (baseImages.at(i).width() * baseImages.at(i).height());
    }

    QFile file(targetFile);

    result = (file.open(QIODevice::WriteOnly | QIODevice::Text));

    if(result)
    {
        QTextStream out(&file);
        for(int i = 0 ; i < baseImages.size() ; i++)
        {
            const QImage img = baseImages.at(i);

            for(int w = 0 ; w < img.width() ; ++w)
            {
                for(int h = 0 ; h < img.height() ; ++h)
                {
                    QColor pixelColor = img.pixelColor(w, h);

                    //out<<pixelColor.red()<<" "<<pixelColor.green()<<" "<<pixelColor.blue()<<" "<<pixelColor.red()<<" "<<pixelColor.green()<<" "<<pixelColor.blue()<<"\n";
                    out<<w<<" "<<h<<" "<<qPow(pixelColor.red()+pixelColor.green()+pixelColor.blue(),splitFactor)<<"\n";
                    emit makeProgress(occurences++, maxoccur);
                }
            }
        }

        file.close();
    }


    emit endEffect(result);


}
