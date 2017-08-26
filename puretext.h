#ifndef PURETEXT_H
#define PURETEXT_H
#include "puredata.h"
#include <QString>
#include <QVector>
#include <QChar>
class PureText : public PureData
{
public:
    PureText();

    void addLetter(const QChar& c);
    void setText(const QString& t);
    QVector<QChar> getText() const;


private:

    QVector<QChar> text;
};

#endif // PURETEXT_H
