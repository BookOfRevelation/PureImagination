#include "plaintextloader.h"
#include <QFileDialog>
#include "puretext.h"

PlainTextLoader::PlainTextLoader(const QString& n)
    : PureLoader(n)
{
    textPath = "";
}

PureCore::PureType PlainTextLoader::getOutputType()
{
    return PureCore::Text;
}

bool PlainTextLoader::init()
{
    QString p = QFileDialog::getOpenFileName(
                nullptr,
                "Loader",
                PureCore::lastOpenDir,
                "Plain text (*.txt)"
                );
    if(p != "")
    {
        QFile f(p);
        QFileInfo fi(f);
        PureCore::lastOpenDir = fi.absoluteDir().absolutePath();
        textPath = p;
    }

    return p != "";
}


void PlainTextLoader::process()
{
    PureText* txt = new PureText;

    QFile f(textPath);
    f.open(QIODevice::ReadOnly);
    QByteArray content = f.readAll();

    txt->setText(QString(content));

    PureCore::currentData = txt;
    f.close();
}

QVector<QVariant> PlainTextLoader::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(textPath));

    return res;
}

void PlainTextLoader::setParameters(QVector<QVariant> p)
{
    textPath = p[0].toString();
}
