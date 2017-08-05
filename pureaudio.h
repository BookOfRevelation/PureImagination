#ifndef PUREAUDIO_H
#define PUREAUDIO_H

#include "puredata.h"
#include <aquila/global.h>
#include <aquila/source/WaveFile.h>
#include <QString>


class PureAudio : public PureData
{
public:
    PureAudio();

    void setAudio(const QString& filename);

    int getMinimumValue() const;
    int getMaximumValue() const;

    int getValue(int i) const;

    int sampleCount() const;

    QString getName() const;

private:

    Aquila::WaveFile* audio;

    QString name;
};

#endif // PUREAUDIO_H
