#include "imagesaver.h"
#include "pureimage.h"
#include <QFileDialog>
#include <QDebug>
#include <QLayout>

ImageSaver::ImageSaver(const QString &n)
    : PureSaver(n)
{
    widget = new ImageSaverWidget;
}
ImageSaver::~ImageSaver()
{
    delete widget;
}

PureCore::PureType ImageSaver::getInputType()
{
    return PureCore::Image;
}

bool ImageSaver::init()
{    
    return widget->exec() == QDialog::Accepted;
}

void ImageSaver::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);

    for(int i = 0 ; i < data->getImageCount() ; ++i)
    {
        QString baseName = data->getName(i).split(".")[0];
        QString targetPath = widget->baseDir + baseName + widget->ext;
        QImage img = data->getImage(i);
        PureCore::lastTargetDir = widget->baseDir;
        img.save(targetPath);

    }
}

QVector<QVariant> ImageSaver::getParameters() const
{
    QVector<QVariant> res;
    res.clear();
    res.push_back(QVariant(widget->baseDir));
    res.push_back(QVariant(widget->ext));
    return res;
}

void ImageSaver::setParameters(QVector<QVariant> p)
{
    widget->baseDir = p[0].toString();
    PureCore::lastTargetDir = widget->baseDir;
    widget->ext = p[1].toString();

    widget->updateUI();
}


ImageSaverWidget::ImageSaverWidget()
{
    baseDir = "";
    ext = "";

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setLayout(mainLt);

    QBoxLayout* dirLt = new QBoxLayout(QBoxLayout::LeftToRight);
    dirLt->addWidget(new QLabel("Target directory : "));
    dirLe = new QLineEdit();
    dirLe->setReadOnly(true);
    dirLt->addWidget(dirLe);
    loadBtn = new QPushButton("...");
    dirLt->addWidget(loadBtn);

    mainLt->addLayout(dirLt);

    QBoxLayout* nameLt = new QBoxLayout(QBoxLayout::LeftToRight);
    nameLt->addWidget(new QLabel("Format : "));
    extCb = new QComboBox;
    extCb->addItem(".jpg");
    extCb->addItem(".png");
    extCb->addItem(".bmp");
    nameLt->addWidget(extCb);

    mainLt->addLayout(nameLt);

    QBoxLayout* btnLt = new QBoxLayout(QBoxLayout::LeftToRight);
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Cancel");
    btnLt->addWidget(okButton);
    btnLt->addWidget(cancelButton);

    mainLt->addLayout(btnLt);


    connect(cancelButton, &QPushButton::pressed, this, &ImageSaverWidget::reject);
    connect(okButton, &QPushButton::pressed, this, [this]()
    {
        if(dirLe->text() == "")
        {
            reject();
        }
        else
        {
            baseDir = dirLe->text();
            ext = extCb->currentText();
            accept();
        }
    });

    connect(loadBtn, &QPushButton::pressed, this, [this]()
    {
        QString targetPath = QFileDialog::getExistingDirectory(nullptr, QString("Target Directory"),
                                                               PureCore::lastTargetDir,
                                                               QFileDialog::ShowDirsOnly);
        if(targetPath != "")
        {
            dirLe->setText(targetPath + "/");
        }
    });

}
