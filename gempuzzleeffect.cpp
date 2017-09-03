#include "gempuzzleeffect.h"
#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include "pureimage.h"

GemPuzzleEffect::GemPuzzleEffect(const QString &n)
    : PureFilter(n)
{
    gemwidget = new GemWidget();
}

GemPuzzleEffect::~GemPuzzleEffect()
{
    delete gemwidget;
}

bool GemPuzzleEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);
}

void GemPuzzleEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);


        //déplace vers la droite
        {
            int width = img.width();
            int height = img.height();

            float effectiveH = PureCore::getRandom(gemwidget->minH, gemwidget->maxH);
            float effectiveW = PureCore::getRandom(gemwidget->minW, gemwidget->maxW);

            int decalage = width * (effectiveH/100.0);
            int largeur = height * (effectiveW/100.0);



            //taille de l'image traitée
            int repeat = largeur;

            while(repeat < img.height())
            {
                int offset = repeat - largeur;
                //progression du décalage (à quelle hauteur on commence)

                //copiage de la bande, (0,offset), (longueur de l'image, largeur de bande)
                QImage subImage = img.copy(0, offset, width, largeur);
                const QImage subref = subImage;

                for(int i = 0 ; i < subImage.width() ;  i++)
                {
                    for(int j = 0 ; j < subImage.height() ; ++j)
                    {
                        //décale la bande de i+decallage pixel vers la droite
                        img.setPixelColor((i + decalage)%subImage.width(), (j+offset), subref.pixelColor(i, j));
                    }
                }

                //calcul de la prochaine taille de bande
                effectiveW = qrand() % ((gemwidget->maxW + 1) - gemwidget->minW) + gemwidget->minW;
                largeur = height * (effectiveW/100.0);

                //calcul du prochain décalage vers la droite
                effectiveH = qrand() % ((gemwidget->maxH + 1) - gemwidget->minH) + gemwidget->minH;
                decalage = width * (effectiveH/100.0);

                //met à jour la progression
                repeat += largeur;
            }
        }
        //déplace vers le bas
        {
            int width = img.width();
            int height = img.height();

            //decalage %taille de la hauter
            float effectiveH = qrand() % ((gemwidget->maxH + 1) - gemwidget->minH) + gemwidget->minH;
            int decalage = height * (effectiveH/100.0);

            //taille de bande %taille de la longeur
            float effectiveW = qrand() % ((gemwidget->maxW + 1) - gemwidget->minW) + gemwidget->minW;
            int largeur = width * (effectiveW/100.0);



            //taille de l'image traitée
            int repeat = largeur;

            while(repeat < img.width())
            {
                int offset = repeat - largeur;
                //progression du décalage (à quelle longueur on commence)

                //copiage de la bande, (0,longueur de l'image), (longueur de l'image, largeur de bande)
                QImage subImage = img.copy(offset, 0, largeur, height);
                const QImage subref = subImage;

                for(int i = 0 ; i < subImage.width() ;  i++)
                {
                    for(int j = 0 ; j < subImage.height() ; ++j)
                    {
                        //décale la bande de j+decallage pixel vers lle bas
                        img.setPixelColor((i + offset), (j+decalage)%subImage.height(), subref.pixelColor(i, j));
                    }
                }

                //calcul de la prochaine taille de bande
                effectiveW = qrand() % ((gemwidget->maxW + 1) - gemwidget->minW) + gemwidget->minW;
                largeur = width * (effectiveW/100.0);

                //calcul du prochain décalage vers le bas
                effectiveH = qrand() % ((gemwidget->maxH + 1) - gemwidget->minH) + gemwidget->minH;
                decalage = height * (effectiveH/100.0);

                //met à jour la progression
                repeat += largeur;
            }
        }
    }
}


QWidget* GemPuzzleEffect::getParamWidget()
{
    return gemwidget;
}


QVector<QVariant> GemPuzzleEffect::getParameters() const
{
    QVector<QVariant> res;

    res.push_back(QVariant(gemwidget->minH));
    res.push_back(QVariant(gemwidget->maxH));
    res.push_back(QVariant(gemwidget->minW));
    res.push_back(QVariant(gemwidget->maxW));
    return res;
}

void GemPuzzleEffect::setParameters(QVector<QVariant> p)
{
    gemwidget->minH = p[0].toInt();
    gemwidget->maxH = p[1].toInt();
    gemwidget->minW = p[2].toInt();
    gemwidget->maxW = p[3].toInt();

    gemwidget->updateUI();
}

GemWidget::GemWidget()
    : QDialog()
{
    minH = 1;
    maxH = 1;
    minW = 1;
    maxW = 1;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    minHSS = new SlideSpiner("Décallage minimum : ", "%", 1, 1, 99);
    maxHSS = new SlideSpiner("Décallage maximum : ", "%", 1, 1, 99);

    minWSS = new SlideSpiner("Largeur minimale : ", "%", 1, 1, 99);
    maxWSS = new SlideSpiner("Largeur maximale : ", "%", 1, 1, 99);

    processBtn = new QPushButton("Ok");

    mainLt->addWidget(minHSS);
    mainLt->addWidget(maxHSS);
    mainLt->addWidget(minWSS);
    mainLt->addWidget(maxWSS);

    QPushButton* randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &GemWidget::randomize);

    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(minHSS, SlideSpiner::valueChanged, this, GemWidget::onMinHModified);
    connect(maxHSS, SlideSpiner::valueChanged, this, GemWidget::onMaxHModified);
    connect(minWSS, SlideSpiner::valueChanged, this, GemWidget::onMinWModified);
    connect(maxWSS, SlideSpiner::valueChanged, this, GemWidget::onMaxWModified);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);


}

void GemWidget::randomize()
{
    maxH = PureCore::getRandom(maxHSS->getMinimum(), maxHSS->getMaximum());
    minH = PureCore::getRandom(minHSS->getMinimum(), minHSS->getMaximum());
    maxW = PureCore::getRandom(maxWSS->getMinimum(), maxWSS->getMaximum());
    minW = PureCore::getRandom(minWSS->getMinimum(), minWSS->getMaximum());


    updateUI();
}


void GemWidget::onMinHModified(double v)
{
    minH = v;
    maxHSS->setMinimum(v);
}

void GemWidget::onMaxHModified(double v)
{
    maxH = v;
    minHSS->setMaximum(v);
}

void GemWidget::onMinWModified(double v)
{
    minW = v;
    maxWSS->setMinimum(v);
}

void GemWidget::onMaxWModified(double v)
{
    maxW = v;
    minWSS->setMaximum(v);
}


DataWidget* GemPuzzleEffect::getDataWidget()
{
    return dataW;
}
