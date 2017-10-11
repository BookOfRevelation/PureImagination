#include "multiimagetodir.h"
#include "purecore.h"

MultiImageToDir::MultiImageToDir()
{
    imagePaths = QVector<QString>();
    targetPath = QString("");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout* inputLt = new QBoxLayout(QBoxLayout::LeftToRight);
    inputLt->addWidget(new QLabel("Image(s) source(s) :"));
    inputLe = new QLineEdit("");
    inputLe->setReadOnly(true);
    QPushButton* inputBtn = new QPushButton("Charger");

    connect(inputBtn, &QAbstractButton::pressed, this, &MultiImageToDir::onInput);

    inputLt->addWidget(inputLe);
    inputLt->addWidget(inputBtn);

    mainLt->addLayout(inputLt);


    QBoxLayout* outputLt = new QBoxLayout(QBoxLayout::LeftToRight);
    outputLt->addWidget(new QLabel("Répertoire de sortie :"));

    outputLe = new QLineEdit("");
    outputLe->setReadOnly(true);

    QPushButton* outputBtn = new QPushButton("Définir");
    connect(outputBtn, &QAbstractButton::pressed, this, &MultiImageToDir::onOutput);
    outputLt->addWidget(outputLe);
    outputLt->addWidget(outputBtn);

    mainLt->addLayout(outputLt);

    this->setLayout(mainLt);

}

MultiImageToDir::~MultiImageToDir()
{
}

bool MultiImageToDir::isBinded() const
{
    qDebug()<<imagePaths;
    qDebug()<<targetPath;
    return (imagePaths.size() > 0 && targetPath != "");
}


void MultiImageToDir::onInput()
{
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png)");
    QStringList fileNames;
    if(dialog.exec())
    {
        inputLe->setText("");
        fileNames = dialog.selectedFiles();
        QString path;
        foreach (path, fileNames)
        {
            QFile f(path);
            QFileInfo fi(f);
            PureCore::lastOpenDir = fi.absoluteDir().absolutePath();

            imagePaths.push_back(path);
            inputLe->setText(inputLe->text() + " ; " + fi.baseName());
        }
        inputLe->setText(inputLe->text().right(inputLe->text().size()-3));
    }
}

void MultiImageToDir::onOutput()
{
    targetPath = QFileDialog::getExistingDirectory(nullptr, QString("Target Directory"),
                                                   PureCore::lastTargetDir,
                                                   QFileDialog::ShowDirsOnly);
    if(targetPath != "")
    {
        PureCore::lastTargetDir = targetPath;
    }

    outputLe->setText(targetPath);
}


