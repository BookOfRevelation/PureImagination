#include "subliminaleffect.h"
#include <QFileDialog>
#include "pureimage.h"

SubliminalEffect::SubliminalEffect()
    : PureFilter()
{
    widget = new SubliminalWidget;
}

bool SubliminalEffect::init()
{
    return (widget->exec() == QDialog::Accepted);
}

void SubliminalEffect::process()
{
    subImages = widget->subImages;
    int frameSkip = widget->frameSkip;
    int subDuration = widget->subDuration;
    bool repeat = widget->repeat;
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    QVector<QImage> originals;
    originals.clear();
    //copy original images
    for(int i = 0 ; i < data->getImageCount() ; ++i)
    {
        originals.push_back(data->getImage(i));
    }
    //clear the data
    data->clear();

    bool dataBiggest = originals.size() > (subImages.size());
    int mainCursor = 0;
    if(dataBiggest)
    {
        int subCursor = 0;
        for(int i = 0 ; i < originals.size() ; ++i)
        {
            //place les frames n par n
            for(int j = 0 ; j < frameSkip ; ++j)
            {
                if(i+j < originals.size())
                {
                    data->addImage(originals[i+j], QString("seq%1.png").arg(mainCursor++,2,10,QChar('0')));

                }

            }
            i = i+frameSkip-1;
            for(int j = 0 ; j < subDuration ; ++j)
            {
                bool isOk = true;
                if(subCursor >= subImages.size())
                {
                    if(repeat)
                    {
                        subCursor = 0;
                    }
                    else
                    {
                        isOk = false;
                    }
                }
                if(isOk)
                {
                    data->addImage(subImages[subCursor], QString("seq%1.png").arg(mainCursor++,2,10,QChar('0')));
                }


            }
            ++subCursor;
        }
    }
    else
    {
        int subCursor = 0;
        for(int i = 0 ; i < subImages.size() ; ++i)
        {
            //place les frames n par n
            for(int j = 0 ; j < frameSkip ; ++j)
            {
                bool isOk = true;
                if(subCursor >= subImages.size())
                {
                    if(repeat)
                    {
                        subCursor = 0;
                    }
                    else
                    {
                        isOk = false;
                    }
                }
                if(isOk)
                {
                    data->addImage(originals[subCursor++], QString("seq%1.png").arg(mainCursor++,2,10,QChar('0')));
                }

            }
            for(int j = 0 ; j < subDuration ; ++j)
            {

                if(i+j < subImages.size())
                {
                    data->addImage(subImages[i+j], QString("seq%1.png").arg(mainCursor++,2,10,QChar('0')));
                }

            }
        }
    }
}

SubliminalWidget::SubliminalWidget()
    : QDialog()
{
    frameSkip = 1;
    subDuration = 1;
    repeat = false;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    fsSS = new SlideSpiner("Nombre de frame avant interlacement : ", "frame", 1, 1, 120);
    subSS = new SlideSpiner("Durée de l'interlacement: ", "frame", 1, 1, 120);
    repeatSeq = new QCheckBox("Cycler la plus courte séquence");
    repeatSeq->setChecked(false);


    QBoxLayout* imgLt = new QBoxLayout(QBoxLayout::LeftToRight);
    imgLt->addWidget(new QLabel("Images de références : "));
    outputLine = new QLineEdit();
    outputLine->setReadOnly(true);
    imgLt->addWidget(outputLine);
    loadBtn = new QPushButton("Charger...");
    imgLt->addWidget(loadBtn);

    processBtn = new QPushButton("Ok");

    setLayout(mainLt);
    mainLt->addWidget(fsSS);
    mainLt->addWidget(subSS);
    mainLt->addWidget(repeatSeq);
    mainLt->addLayout(imgLt);
    mainLt->addWidget(processBtn);


    connect(fsSS, &SlideSpiner::valueChanged, this, &SubliminalWidget::onFrameSkipModified);
    connect(subSS, &SlideSpiner::valueChanged, this, &SubliminalWidget::onSubDurationModified);
    connect(repeatSeq, &QCheckBox::pressed, this, [this]()
    {
       repeat = !repeatSeq->isChecked();
    });
    connect(loadBtn, &QPushButton::pressed, this, &SubliminalWidget::onImageLoad);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);
}

void SubliminalWidget::onFrameSkipModified(double v)
{
    frameSkip = v;
}


void SubliminalWidget::onSubDurationModified(double v)
{
    subDuration = v;
}

void SubliminalWidget::onImageLoad()
{
    subImages.clear();
    outputLine->setText("");
    QStringList filePath;
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png)");
    if(dialog.exec())
    {
        filePath = dialog.selectedFiles();
        PureCore::lastOpenDir = dialog.directory().absolutePath();
        QString name;
        foreach (name, filePath)
        {

            subImages.push_back(QImage(name));
            outputLine->setText(outputLine->text() + name + "; ");
        }
    }

}
