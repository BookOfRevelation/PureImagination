#include "gifsaver.h"
#include "pureimage.h"
#include <QFileDialog>
#include <QRgb>
#include "gif.h"
#include <QDebug>


GifSaver::GifSaver(const QString &n)
    : PureSaver(n)
{
    widget = new GifSaverWidget;
}

GifSaver::~GifSaver()
{
    delete widget;
}

PureCore::PureType GifSaver::getInputType()
{
    return PureCore::Image;
}

bool GifSaver::init()
{
    return widget->exec() == QDialog::Accepted;
}

void GifSaver::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    QImage firstImage = data->getImage(0);
    GifWriter* w = new GifWriter();

    QString targetPath = widget->baseDir;
    GifBegin(w, (targetPath + "gifresult.gif").toStdString().c_str(), firstImage.width(), firstImage.height(),widget->speed);
    GifWriteFrame(w ,firstImage.bits(), firstImage.width(), firstImage.height(),widget->speed);


    for(int i = 1 ; i < data->getImageCount() ; ++i)
    {
        QImage curImg = data->getImage(i);
        curImg = curImg.scaled(firstImage.width(), firstImage.height());
        GifWriteFrame(w ,curImg.bits(), curImg.width(), curImg.height(),widget->speed);
    }
    GifEnd(w);

}

QVector<QVariant> GifSaver::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(QVariant(widget->speed));
    res.push_back(QVariant(widget->baseDir));

    return res;
}

void GifSaver::setParameters(QVector<QVariant> p)
{
    widget->speed = p[0].toInt();
    widget->baseDir= p[1].toString();

    widget->updateUI();
}


GifSaverWidget::GifSaverWidget()
{
    baseDir = "";
    speed = 1;

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

    speedSS = new SlideSpiner("Delay", "cs", 1, 4, 100);
    connect(speedSS, &SlideSpiner::valueChanged, this, [this](double c)
    {
        this->speed = c;
    });

    mainLt->addWidget(speedSS);


    QBoxLayout* btnLt = new QBoxLayout(QBoxLayout::LeftToRight);
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Cancel");
    btnLt->addWidget(okButton);
    btnLt->addWidget(cancelButton);

    mainLt->addLayout(btnLt);


    connect(cancelButton, &QPushButton::pressed, this, &GifSaverWidget::reject);
    connect(okButton, &QPushButton::pressed, this, [this]()
    {
        if(dirLe->text() == "")
        {
            reject();
        }
        else
        {
            baseDir = dirLe->text();
            speed = speedSS->getValue();
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
