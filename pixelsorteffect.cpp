#include "pixelsorteffect.h"
#include "pureimage.h"

#include <QBoxLayout>

PixelSortEffect::PixelSortEffect(const QString & n)
    : PureFilter(n)
{
    widget = new PixelSortWidget();
}

PixelSortEffect::~PixelSortEffect()
{
    delete widget;
}

bool PixelSortEffect::init()
{
    return (widget->exec() == QDialog::Accepted);
}

void PixelSortEffect::process()
{
    QString type = widget->sortingType;
    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    for(int nbimg = 0 ; nbimg < data->getImageCount() ; ++nbimg)
    {
        QImage& img = data->getImage(nbimg);
        for(int i = 0 ; i < img.width() ; ++i)
        {
            std::vector<QColor> luminances;
            luminances.clear();
            for(int j = 0 ; j < img.height() ; ++j)
            {
                luminances.push_back(img.pixelColor(i,j));
            }

            std::sort(luminances.begin(), luminances.end(), [type](QColor c1, QColor c2)
            {
                bool operation;
                if(type == "Value")
                {
                    operation = c1.value() < c2.value();
                }
                else if(type == "Color")
                {
                    operation = c1.hue() < c2.hue();
                }
                else if(type == "Saturation")
                {
                    operation = c1.saturation() < c2.saturation();
                }
                return operation;
            });

            for(int j = 0 ; j < img.height() ; ++j)
            {
                img.setPixelColor(i, j, luminances.at(j));
            }
        }
    }
}

QWidget* PixelSortEffect::getParamWidget()
{
    return widget;
}

QVector<QVariant> PixelSortEffect::getParameters() const
{
    QVector<QVariant> res;
    res.clear();

    res.push_back(widget->sortingType);
    res.push_back(widget->sortingShape);

    return res;
}

void PixelSortEffect::setParameters(QVector<QVariant> p)
{
    widget->sortingType = p[0].toString();
    widget->sortingShape = p[1].toString();

    widget->updateUI();
}

PixelSortWidget::PixelSortWidget()
{
    sortingType = "Value";
    sortingShape = "Vertical";

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    typeCB = new QComboBox();
    typeCB->addItem("Value");
    typeCB->addItem("Color");
    typeCB->addItem("Saturation");

    shapeCB = new QComboBox();
    shapeCB->addItem("Vertical");

    processBtn = new QPushButton("Ok");

    mainLt->addWidget(typeCB);
    mainLt->addWidget(shapeCB);

    randomBtn = new QPushButton("Randomize");
    mainLt->addWidget(randomBtn);
    connect(randomBtn, &QPushButton::pressed, this, &PixelSortWidget::randomize);

    mainLt->addWidget(processBtn);

    this->setLayout(mainLt);

    connect(typeCB, &QComboBox::currentTextChanged, this, [this](const QString& t)
    {
        sortingType = t;
    });


    connect(shapeCB, &QComboBox::currentTextChanged, this, [this](const QString& t)
    {
        sortingShape = t;
    });

    connect(processBtn, &QAbstractButton::pressed, this, &QDialog::accept);
}

void PixelSortWidget::randomize()
{
    sortingType = typeCB->itemText(PureCore::getRandom(0, typeCB->count()));
    sortingShape = shapeCB->itemText(PureCore::getRandom(0, typeCB->count()));

    updateUI();
}
