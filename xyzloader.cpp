#include "xyzloader.h"
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QDebug>

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
        float x, y, z;

        x = strs.at(0).toFloat();
        y = strs.at(1).toFloat();
        z = strs.at(2).toFloat();
        xyz->addPoint(
                    x,
                    y,
                    z
                    );
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
