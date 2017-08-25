#include "puretext.h"

PureText::PureText()
    : PureData()
{
    text = "";
}


void PureText::setText(const QString &t)
{
    text = t;
}

QString PureText::getText() const
{
    return text;
}
