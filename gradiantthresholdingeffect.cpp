#include "gradiantthresholdingeffect.h"
#include "purecore.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>

GradiantThresholdingEffect::GradiantThresholdingEffect(const QString &n)
    : PureFilter(n), sequence(false), targetDir("")
{
    gemwidget = new GradiantThresholdingWidget(this);
}

GradiantThresholdingEffect::~GradiantThresholdingEffect()
{
    delete gemwidget;
}

bool GradiantThresholdingEffect::init()
{
    bool result = false;

    baseImages.clear();
    resultImages.clear();

    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png)");
    QStringList fileNames;
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        QString path;
        foreach (path, fileNames)
        {
            QFile f(path);
            QFileInfo fi(f);
            PureCore::lastOpenDir = fi.absoluteDir().absolutePath();
            baseImages.push_back(QPair<QImage, QString>(QImage(path), fi.fileName()));
        }

        targetDir = QFileDialog::getExistingDirectory(nullptr, QString("Target Directory"),
                                                      PureCore::lastTargetDir,
                                                      QFileDialog::ShowDirsOnly);

        result = (targetDir != "");
        if(result)
        {
            PureCore::lastTargetDir = targetDir;
        }
        qDebug()<<targetDir;
    }

    return result;

}

void GradiantThresholdingEffect::process()
{

    QPair<QImage,QString> pair;

    bool result = true;
    int seuil = gemwidget->seuil;
    int occurences = 0;
    int maxoccur = baseImages.size();

    foreach(pair, baseImages)
    {
         emit makeProgress(occurences++, maxoccur);
        //image de base
        QImage img = pair.first;

        for(int i = 0 ; i < img.width() ; ++i)
        {
            for(int j = 0 ; j < img.height() ; ++j)
            {
                QColor c = img.pixelColor(i, j);

                if(c.red() + c.green() + c.blue() >= seuil)
                {
                    img.setPixelColor(i, j, QColor(255,255,255));
                }
                else
                {
                    img.setPixelColor(i, j, QColor(i%255,(i*j)%255,(i+j)%255));
                }
            }
        }

        //sauve l'image finale
        result = result && img.save(targetDir+QString("/")+pair.second);

    }
    emit endEffect(result);
}


QWidget* GradiantThresholdingEffect::getParamWidget()
{
    return gemwidget;
}


GradiantThresholdingWidget::GradiantThresholdingWidget(GradiantThresholdingEffect* effect)
    : QWidget(), burgle(effect)
{
    seuil = 3;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    seuilSS = new SlideSpiner("Seuil : ", " ", 1, 1, 255);

    processBtn = new QPushButton("Process");

    mainLt->addWidget(seuilSS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(seuilSS, SlideSpiner::valueChanged, this, GradiantThresholdingWidget::onSeuilModified);

    connect(processBtn, QAbstractButton::pressed, this, [this]()
    {
        this->burgle->process();
    });

}


void GradiantThresholdingWidget::onSeuilModified(double v)
{
    seuil = 3*v;
}

