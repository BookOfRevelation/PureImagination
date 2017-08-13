#include "wavloader.h"
#include <QFileDialog>
#include "pureaudio.h"
#include <QDebug>

WavLoader::WavLoader(const QString &n)
    : PureLoader(n)
{
    filePath = "";
}
bool WavLoader::init()
{
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Wave (*.wav)");
    if(dialog.exec())
    {
        filePath = dialog.selectedFiles()[0];
        PureCore::lastOpenDir = dialog.directory().absolutePath();

    }
    else
    {
        filePath = "";
    }

    return filePath !="";
}

void WavLoader::process()
{
    PureAudio* audio = new PureAudio;
    audio->setAudio(filePath);

    PureCore::currentData = audio;
}


QVector<QVariant> WavLoader::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(filePath));

    return res;
}

void WavLoader::setParameters(QVector<QVariant> p)
{
    filePath = p[0].toString();
}
