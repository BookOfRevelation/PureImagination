#include "xyzloader.h"
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QString>

XYZLoader::XYZLoader(const QString& n)
    : PureLoader(n)
{
    filePath = "";
}

bool XYZLoader::init()
{
    filePath = QFileDialog::getOpenFileName(
                nullptr,
                "open cloud point",
                PureCore::lastOpenDir,
                "3D Point Cloud (*.xyz, *.pts, *.txt)"
                );

    if(filePath != "")
    {
        QFile f(filePath);
        QFileInfo fi(f);
        PureCore::lastOpenDir = fi.absoluteDir().absolutePath();
    }

    return filePath != "";
}

void XYZLoader::process()
{
    PureXYZ* xyz = new PureXYZ;
    QFile f(filePath);

    f.open(QIODevice::ReadOnly);

    QTextStream ts(&f);

    QString line = ts.readLine();
    while(!line.isNull())
    {
        QStringList strs = line.split(" ");
        xyz->addPoint(strs.at(0).toInt(), strs.at(1).toInt(), strs.at(2).toInt());
        line = ts.readLine();
    }

    PureCore::currentData = xyz;
}


void XYZLoader::setParameters(QVector<QVariant> p)
{
    filePath = p[0].toString();
}

QVector<QVariant> XYZLoader::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(filePath));

    return res;
}
