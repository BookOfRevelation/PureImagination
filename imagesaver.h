#ifndef IMAGESAVER_H
#define IMAGESAVER_H
#include "puresaver.h"
#include <QVariant>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>

class ImageSaverWidget : public QDialog
{
    Q_OBJECT

public:
    ImageSaverWidget();

    void updateUI()
    {
        dirLe->setText(baseDir);
        extCb->setCurrentIndex(extCb->findText(ext));
    }

//PARAMETERS
    QString baseDir;
    QString ext;

private:

    QLineEdit* dirLe;
    QComboBox* extCb;
    QPushButton* loadBtn;

    QPushButton* okButton;
    QPushButton* cancelButton;



};

class ImageSaver : public PureSaver
{
public:
    ImageSaver(const QString &n);

    PureCore::PureType getInputType();

    bool init();
    void process();

    PureEffect* clone()
    {
        ImageSaver* e = new ImageSaver(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Saver Image",
                    "Enregistre le résultat d'une chaîne\n"
                    "de traitement sous la forme d'une\n"
                    "séquence d'image dans un dossier\n"
                    "du disque dur."
                    );
    }

private:

    ImageSaverWidget* widget;

};

#endif // IMAGESAVER_H
