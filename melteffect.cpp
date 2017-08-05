#include "melteffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

MeltEffect::MeltEffect()
    : PureFilter(), fileName("")
{

}

bool MeltEffect::init()
{
    QString filePath;
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Images (*.jpg *.png)");
    if(dialog.exec())
    {
        filePath = dialog.selectedFiles()[0];
        PureCore::lastOpenDir = dialog.directory().absolutePath();
        melting.load(filePath);
    }
    else
    {
        filePath = "";
    }

    return filePath !="";
}

void MeltEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    QImage ref = melting;

    for(int i = 0 ; i < data->getImageCount() ; i++)
    {
        QImage& img = data->getImage(i);
        img = img.scaled(ref.width(), ref.height());
    }

    for(int w = 0 ; w < ref.width() ; ++w)
    {
        for(int h = 0 ; h < ref.height() ; ++h)
        {

            QColor bc = ref.pixelColor(w,h);
            bc = bc.toHsv();

            int hue = 0;
            int saturation = 0;
            int value = 0;

            for(int i = 0 ; i < data->getImageCount(); ++i)
            {
                QImage& current = data->getImage(i);
                QColor pc = current.pixelColor(w,h);
                pc = pc.toHsv();

                saturation = (bc.saturation() + pc.saturation())/2;
                value = (bc.value() + pc.value())/2;
                hue = (bc.hue() + pc.hue())/2;


                current.setPixelColor(w, h, QColor::fromHsv(hue, saturation, value));


            }


        }
    }

}
