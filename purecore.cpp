#include "purecore.h"
#include <QTime>
#include <QDir>
#include <QBoxLayout>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsBlurEffect>

QString PureCore::lastOpenDir;
QString PureCore::lastTargetDir;
PureCore::PureType PureCore::currentOutput;
PureData* PureCore::currentData;
PureImage* PureCore::noFragement;
PureCondition* PureCore::condition;
QVector<QVector<bool>> PureCore::conditionPoints;

PureCore::PureCore()
{
    lastOpenDir = QDir::homePath();
    lastTargetDir = QDir::homePath();

    currentOutput = NoType;

    noFragement = nullptr;
    condition = nullptr;
}

void PureCore::initRNG()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}


int PureCore::getRandom(int min, int max)
{
    int rd = qrand() % ((max + 1) - min) + min;

    return rd;
}


QWidget* PureCore::getEmptyWidget(const QString &lbl)
{
    QWidget* res = new QWidget;
    QBoxLayout* lt = new QBoxLayout(QBoxLayout::TopToBottom);

    res->setLayout(lt);
    QLabel* lblw = new QLabel(lbl);
    lt->addWidget(lblw);

    return res;
}


QString PureCore::TypeToStr(PureType n)
{
    QString result = "";

    switch(n)
    {
    case PureCore::NoType : result = "none"; break;
    case PureCore::Image  : result = "images"; break;
    case PureCore::XYZ    : result = "point cloud"; break;
    case PureCore::Wave   : result = "wave audio"; break;
    case PureCore::Text   : result = "plain text"; break;
    }

    return result;
}

QImage PureCore::applyEffectToImage(QImage src, int blur,  int extent)
{
    if(src.isNull()) return QImage();   //No need to do anything else!
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    QGraphicsBlurEffect* be = new QGraphicsBlurEffect;
    be->setBlurRadius(blur);
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(be);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );

    delete be;

    return res;
}
