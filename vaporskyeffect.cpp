#include "vaporskyeffect.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>

VaporSkyEffect::VaporSkyEffect(const QString &n)
    : PureFilter(n),sequence(false), targetDir("")
{
    gemwidget = new VaporSkyWidget(this);
}

VaporSkyEffect::~VaporSkyEffect()
{
    delete gemwidget;
}

bool VaporSkyEffect::init()
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
        QString bgpath = QFileDialog::getOpenFileName(nullptr, QString("Background image"), QDir::homePath(), QString("Images (*.jpg *.png"));
        if(bgpath != "")
        {
            bgimg.load(bgpath);

            targetDir = QFileDialog::getExistingDirectory(nullptr, QString("Target Directory"),
                                                          PureCore::lastTargetDir,
                                                          QFileDialog::ShowDirsOnly);

            result = (targetDir != "");
            if(result)
            {
                PureCore::lastTargetDir = targetDir;
            }
        }

    }

    return result;

}

void VaporSkyEffect::process()
{

    QPair<QImage,QString> pair;

    int seuil = gemwidget->seuil;
    bool result = true;
    int occurences = 0;
    int maxoccur = baseImages.size();

    foreach(pair, baseImages)
    {
        emit makeProgress(occurences++, maxoccur);
        //image de base
        QImage img = pair.first;


        QImage scbg = bgimg.scaled(img.width(), img.height());

        for(int i = 0 ; i < img.width() ; ++i)
        {
            for(int j = 0 ; j < img.height() ; ++j)
            {
                QColor c = img.pixelColor(i, j);

                if(c.red() + c.green() + c.blue() > seuil)
                {
                    img.setPixelColor(i, j, scbg.pixelColor(i,j));
                }
            }
        }

        //sauve l'image finale
        result = result && img.save(targetDir+QString("/")+pair.second);

    }

    emit endEffect(result);
}


QWidget* VaporSkyEffect::getParamWidget()
{
    return gemwidget;
}


VaporSkyWidget::VaporSkyWidget(VaporSkyEffect* effect)
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

    connect(seuilSS, SlideSpiner::valueChanged, this, VaporSkyWidget::onSeuilModified);

    connect(processBtn, QAbstractButton::pressed, this, [this]()
    {
        this->burgle->process();
    });

}


void VaporSkyWidget::onSeuilModified(double v)
{
    seuil = 3*v;
}

