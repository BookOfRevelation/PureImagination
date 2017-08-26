#include "puretext.h"
#include <QVector>
#include <QChar>
PureText::PureText()
    : PureData()
{
    text.clear();
}

void PureText::addLetter(const QChar &c)
{
    text.push_back(c);
}


void PureText::setText(const QString &t)
{
    text.clear();
    for(int i = 0 ; i < t.size() ; ++i)
    {
        text.push_back(t.at(i));
    }
}

QVector<QChar> PureText::getText() const
{
    return text;
}
