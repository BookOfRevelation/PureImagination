#include "gifloader.h"
#include <QFileDialog>
#include "pureimage.h"
#include <QMovie>

GifLoader::GifLoader(const QString &n)
    : PureLoader(n)
{
    filePath = "";

}

PureCore::PureType GifLoader::getOutputType()
{
    return PureCore::Image;

}

bool GifLoader::init()
{
    filePath = QFileDialog::getOpenFileName(
                nullptr,
                "Charger un Gif",
                PureCore::lastOpenDir,
                tr("Gif (*.gif)")
                );

    return filePath != "";

}

void GifLoader::process()
{
    PureImage* imgs = new PureImage;

    QFile f(filePath);
    QFileInfo fi(f);


    QMovie animated(filePath);
    animated.stop();

    for(int i = 0; i < animated.frameCount() ; ++i)
    {
        QString name = QString("%1%2.png").arg(fi.baseName()).arg(QString::number(i));
        animated.jumpToFrame(i);
        imgs->addImage(animated.currentImage(), name );
    }


    PureCore::currentData = imgs;

}

QVector<QVariant> GifLoader::getParameters() const
{
    QVector<QVariant> res;
    res.clear();
    res.push_back(QVariant(filePath));
    return res;
}

void GifLoader::setParameters(QVector<QVariant> p)
{
    filePath = p[0].toString();
}
