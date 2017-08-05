#include "anaglypheffect.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include <QDialog>
#include "pureimage.h"

AnaglyphEffect::AnaglyphEffect():
    PureFilter()
{
    gemwidget = new AnaglyphWidget;
}

AnaglyphEffect::~AnaglyphEffect()
{
    delete gemwidget;
}


bool AnaglyphEffect::init()
{
    return (gemwidget->exec() == QDialog::Accepted);
}

void AnaglyphEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);


    for(int nbimg = 0 ; nbimg < data->getImageCount() ; nbimg++)
    {
        //image de base
        QImage& img = data->getImage(nbimg);
        QImage redi = img.copy();
        QImage greeni = img.copy();
        QImage bluei = img.copy();

        //create images
        for(int i = 0 ; i < redi.width() ; ++i)
        {
            for(int j = 0 ; j < redi.height() ; ++j)
            {
                int newrx = (i-gemwidget->rx);
                if(newrx >= img.width())
                {
                    //newrx = img.width()-newrx;
                    newrx = i;
                }
                else if(newrx < 0)
                {
                    //newrx = img.width() + newrx -1;
                    newrx = i;
                }
                int newry = (j-gemwidget->ry);
                if(newry >= img.height())
                {
                    //newry = img.height()-newry;
                    newry = j;
                }
                else if(newry < 0)
                {
                    //newry = img.height() + newry -1;
                    newry = j;
                }


                int newgx = (i-gemwidget->gx);
                if(newgx >= img.width())
                {
                    //newgx = img.width()-newgx;
                    newgx = i;
                }
                else if(newgx < 0)
                {
                    //newgx = img.width() + newgx -1;
                    newgx = i;
                }
                int newgy = (j-gemwidget->gy);
                if(newgy >= img.height())
                {
                    //newgy = img.height()-newgy;
                    newgy = j;
                }
                else if(newgy < 0)
                {
                    //newgy = img.height() + newgy -1;
                    newgy= j;
                }



                int newbx = (i-gemwidget->bx);
                if(newbx >= img.width())
                {
                    //newbx = img.width()-newbx;
                    newbx= i;
                }
                else if(newbx < 0)
                {
                    //newbx = img.width() + newbx -1;
                    newbx= i;
                }
                int newby = (j-gemwidget->by);
                if(newby >= img.height())
                {
                    //newby = img.height()-newby;
                    newby= j;
                }
                else if(newby < 0)
                {
                    //newby = img.height() + newby -1;
                    newby =j;
                }



                QColor rc = img.pixelColor(
                            newrx, newry
                            );
                QColor gc = img.pixelColor(
                            newgx, newgy
                            );
                QColor bc = img.pixelColor(
                            newbx, newby
                            );

                redi.setPixelColor(i, j, QColor(rc.red(), 0, 0));
                greeni.setPixelColor(i, j ,QColor(0,gc.green(), 0));
                bluei.setPixelColor(i, j, QColor(0, 0, bc.blue()));
            }
        }

        //translate images

        for(int i = 0 ; i < img.width() ; ++i)
        {
            for(int j = 0 ; j < img.height() ; ++j)
            {
                QColor rc = redi.pixelColor(i,j);
                QColor gc = greeni.pixelColor(i, j);
                QColor bc = bluei.pixelColor(i, j);

                img.setPixelColor(i, j,
                                  QColor(
                                      (rc.red() + gc.red() + bc.red() ),
                                      (rc.green() + gc.green() + bc.green() ),
                                      (rc.blue() + gc.blue() + bc.blue() )
                                      )
                                  );


            }
        }




    }
}


QWidget* AnaglyphEffect::getParamWidget()
{
    return gemwidget;
}


AnaglyphWidget::AnaglyphWidget()
    : QDialog()
{
    rx = ry = gx = gy = bx = by = 0;
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    rxSS = new SlideSpiner("Red offset x : ", "px", 1, -100, 100);
    rxSS->setValue(0);
    rySS = new SlideSpiner("Red offset y : ", "px", 1, -100, 100);
    rySS->setValue(0);
    gxSS = new SlideSpiner("Green offset x : ", "px", 1, -100, 100);
    gySS = new SlideSpiner("Green offset y : ", "px", 1, -100, 100);

    bxSS = new SlideSpiner("Blue offset x : ", "px", 1, -100, 100);
    bySS = new SlideSpiner("Blue offset y : ", "px", 1, -100, 100);

    gxSS->setValue(0);
    gySS->setValue(0);
    bxSS->setValue(0);
    bySS->setValue(0);

    processBtn = new QPushButton("Ok");

    mainLt->addWidget(rxSS);
    mainLt->addWidget(rySS);
    mainLt->addWidget(gxSS);
    mainLt->addWidget(gySS);
    mainLt->addWidget(bxSS);
    mainLt->addWidget(bySS);
    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(rxSS, SlideSpiner::valueChanged, this, AnaglyphWidget::onRX);
    connect(rySS, SlideSpiner::valueChanged, this, AnaglyphWidget::onRY);
    connect(gxSS, SlideSpiner::valueChanged, this, AnaglyphWidget::onGX);
    connect(gySS, SlideSpiner::valueChanged, this, AnaglyphWidget::onGY);
    connect(bxSS, SlideSpiner::valueChanged, this, AnaglyphWidget::onBX);
    connect(bySS, SlideSpiner::valueChanged, this, AnaglyphWidget::onBY);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);


}


void AnaglyphWidget::onRX(double v)
{
    rx = v;
}
void AnaglyphWidget::onRY(double v)
{
    ry = v;
}
void AnaglyphWidget::onGX(double v)
{
    gx = v;
}
void AnaglyphWidget::onGY(double v)
{
    gy = v;
}
void AnaglyphWidget::onBX(double v)
{
    bx = v;
}
void AnaglyphWidget::onBY(double v)
{
    by = v;
}


