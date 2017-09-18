#include "xyzsaver.h"
#include "purexyz.h"
#include <QTextStream>
#include <QDebug>
XYZSaver::XYZSaver(const QString& n)
    : PureSaver(n)
{
    path = "";
}

bool XYZSaver::init()
{

    path = QFileDialog::getExistingDirectory(
                nullptr,
                "output folder",
                PureCore::lastTargetDir,
                QFileDialog::ShowDirsOnly
                );
    qDebug()<<path;
    if(path !="")
    {
        PureCore::lastTargetDir = path;
    }
    return path != "";
}
void XYZSaver::process()
{
    PureXYZ* data = static_cast<PureXYZ*>(PureCore::currentData);
    QString fullpath = path + QString("/pointcloud.txt");
    qDebug()<<fullpath;
    QFile file(fullpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i = 0 ; i < data->count() ; ++i)
    {
        QVector3D pt = data->getPoint(i);

        out<<static_cast<int>(pt.x())<<" "<<static_cast<int>(pt.y())<<" "<<static_cast<int>(pt.z())<<"\n";
    }

    file.close();
}
