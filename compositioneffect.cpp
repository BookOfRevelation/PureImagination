#include "compositioneffect.h"

#include <QFileDialog>
#include <QDebug>
#include <QBoxLayout>
#include <QTime>
#include <QtMath>
#include "pureimage.h"
#include <QVector3D>
CompositionEffect::CompositionEffect(const QString &n)
    : PureFilter(n)
{
    widget = new CompositionWidget;
}



bool CompositionEffect::init()
{
    return (widget->exec() == QDialog::Accepted);
}

void CompositionEffect::process()
{
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    //QImage ref = refImage;
    int pixelDim = widget->pixelDim;

    QVector<QImage> &refImages = widget->pixelImages;

    images.clear();
    colors.clear();

    for(int i = 0 ; i < refImages.size() ; i++)
    {
        QImage img = refImages[i];
        int rsum = 0;
        int gsum = 0;
        int bsum = 0;
        int coef = img.width() * img.height();
        for(int w = 0 ; w < img.width() ; ++w)
        {
            for(int h = 0 ; h < img.height() ; ++h)
            {
                QColor c = img.pixelColor(w,h);
                rsum += c.red();
                gsum += c.green();
                bsum += c.blue();

            }
        }

        rsum /= coef;
        gsum /= coef;
        bsum /= coef;

        images.push_back(img.scaled(pixelDim, pixelDim));
        colors.push_back(QColor(rsum, gsum, bsum));

    }

    for(int i = 0 ; i < data->getImageCount() ; i++)
    {
        QImage& img = data->getImage(i);
        for(int i = 0 ; i < img.width() ; i = i + pixelDim)
        {
            for(int j = 0 ; j < img.height() ; j = j + pixelDim)
            {
                //find the mean color
                QColor mean;
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                int coef = 0;
                for(int x = 0; x < pixelDim ; ++x)
                {
                    for(int y = 0 ; y < pixelDim ; ++y)
                    {
                        if(i + x < img.width() && j + y < img.height())
                        {
                            QColor c = img.pixelColor(i + x, j + y);
                            rsum += c.red();
                            gsum += c.green();
                            bsum += c.blue();
                            ++coef ;
                        }

                    }
                }
                rsum /= coef;
                gsum /= coef;
                bsum /= coef;

                mean.setRgb(rsum, gsum, bsum);

                //find the nearest img
                QImage replaceImg = neareastColor(mean);

                //replace pixels
                for(int x = 0 ; x < pixelDim ; ++x)
                {
                    for(int y = 0 ; y < pixelDim; ++y)
                    {
                        if(i + x < img.width() && j + y < img.height())
                        {
                            img.setPixelColor(i+x, j+y, replaceImg.pixelColor(x, y));
                        }
                    }
                }
            }
        }
    }


}

QImage CompositionEffect::neareastColor(QColor c1)
{
    int minIndex = 0;
    float mindist;
    QColor c2 = colors[0];

    mindist = QVector3D(c1.red(), c1.green(), c1.blue()).distanceToPoint(QVector3D(c2.red(), c2.green(), c2.blue()));

    //find the nearest point
    for(int i = 1 ; i < colors.size() ; ++i)
    {
        c2 = colors[i];
        float dist = QVector3D(c1.red(), c1.green(), c1.blue()).distanceToPoint(QVector3D(c2.red(), c2.green(), c2.blue()));
        if(dist < mindist)
        {
            mindist = dist;
            minIndex = i;
        }
    }

    return images[minIndex];

}


CompositionWidget::CompositionWidget()
    : QDialog()
{
    pixelDim = 2;
    pixelImages.clear();
    setWindowTitle("param");

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    pixelSS = new SlideSpiner("Taille des pixels : ", "px", 1, 2, 640);


    QBoxLayout* imgLt = new QBoxLayout(QBoxLayout::LeftToRight);
    imgLt->addWidget(new QLabel("Images de références : "));
    outputLine = new QLineEdit();
    outputLine->setReadOnly(true);
    imgLt->addWidget(outputLine);
    loadBtn = new QPushButton("Charger...");
    imgLt->addWidget(loadBtn);

    processBtn = new QPushButton("Ok");

    setLayout(mainLt);
    mainLt->addWidget(pixelSS);
    mainLt->addLayout(imgLt);
    mainLt->addWidget(processBtn);


    connect(pixelSS, &SlideSpiner::valueChanged, this, &CompositionWidget::onPixelModified);
    connect(loadBtn, &QPushButton::pressed, this, &CompositionWidget::onImageLoad);
    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);
}


void CompositionWidget::onPixelModified(double v)
{
   pixelDim = static_cast<int>(v);
}

void CompositionWidget::onImageLoad()
{
    pixelImages.clear();
    outputLine->setText("");
    QStringList filePath;
    QFileDialog dialog(nullptr);
    dialog.setDirectory(PureCore::lastOpenDir);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images (*.jpg *.png *.gif)");
    if(dialog.exec())
    {
        filePath = dialog.selectedFiles();
        PureCore::lastOpenDir = dialog.directory().absolutePath();
        QString name;
        foreach (name, filePath)
        {

            pixelImages.push_back(QImage(name));
            outputLine->setText(outputLine->text() + name + "; ");
        }
    }

}
