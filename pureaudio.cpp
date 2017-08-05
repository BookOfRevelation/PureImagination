#include "pureaudio.h"
#include <QFile>
#include <QFileInfo>

PureAudio::PureAudio()
    :
    audio(nullptr)
{

}


void PureAudio::setAudio(const QString &filename)
{
    audio = new Aquila::WaveFile(filename.toStdString());
    QFile f(filename);
    QFileInfo fi(f);
    name = fi.fileName();
}

int PureAudio::getMinimumValue() const
{
     Aquila::SampleType minValue = 0;
    // iterator usage
    for (auto it = audio->begin(); it != audio->end(); ++it)
    {
        if (qAbs(*it) < minValue)
            minValue = qAbs(*it);
    }

    return minValue;
}

int PureAudio::getMaximumValue() const
{
    Aquila::SampleType maxValue = 0;
    for (std::size_t i = 0; i < audio->getSamplesCount(); ++i)
    {
        if (qAbs(audio->sample(i)) > maxValue)
            maxValue = qAbs(audio->sample(i));
    }

    return maxValue;
}

int PureAudio::getValue(int i) const
{
    return audio->sample(i);
}

int PureAudio::sampleCount() const
{
    return audio->getSamplesCount();
}

QString PureAudio::getName() const
{
    return this->name;
}
