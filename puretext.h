#ifndef PURETEXT_H
#define PURETEXT_H
#include "puredata.h"
#include <QString>
class PureText : public PureData
{
public:
    PureText();

    void setText(const QString& t);
    QString getText() const;


private:

    QString text;
};

#endif // PURETEXT_H
