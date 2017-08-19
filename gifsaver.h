#ifndef GIFSAVER_H
#define GIFSAVER_H
#include "puresaver.h"
#include "slidespiner.h"
#include <QVariant>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>

class GifSaverWidget : public QDialog
{
    Q_OBJECT

public:

    GifSaverWidget();
    void updateUI()
    {
        speedSS->setValue(speed);
        dirLe->setText(baseDir);
    }


//PARAMETERS
    int speed;
    QString baseDir;

private:
    SlideSpiner* speedSS;

    QLineEdit* dirLe;
    QPushButton* loadBtn;

    QPushButton* okButton;
    QPushButton* cancelButton;

};

class GifSaver : public PureSaver
{
public:
    GifSaver(const QString &n);
    ~GifSaver();

    PureCore::PureType getInputType();

    bool init();
    void process();

    PureEffect* clone()
    {
        GifSaver* e = new GifSaver(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Saver Gif",
                    "Enregistre le résultat d'une chaîne\n"
                    "de traitement sous la forme d'un\n"
                    "gif animé dans un dossier\n"
                    "du disque dur."
                    );
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

private:

    GifSaverWidget* widget;
};

#endif // GIFSAVER_H
