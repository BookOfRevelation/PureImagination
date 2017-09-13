#include "imagetofragment.h"
#include "purecondition.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>

ImageToFragment::ImageToFragment(const QString& n)
    : PureTransformater(n)
{
    widget = new FragmentWidget();
}

ImageToFragment::~ImageToFragment()
{
    delete widget;
}

bool ImageToFragment::init()
{
    if(widget->exec() == QDialog::Accepted)
    {
        if(PureCore::noFragement != nullptr)
        {
            delete PureCore::noFragement;
            PureCore::noFragement = nullptr;

            delete PureCore::condition;
            PureCore::condition = nullptr;
        }
        PureCore::noFragement = new PureImage();
        return true;
    }
    else
    {
        return false;
    }


}

void ImageToFragment::process()
{

    PureImage* data = static_cast<PureImage*>(PureCore::currentData);
    for(int i = 0 ; i < data->getImageCount() ; ++i)
    {
        PureCore::noFragement->addImage(data->getImage(i), data->getName(i));
    }

    PureCore::condition = new EvenCondition();
    PureCore::condition->init();

}

FragmentWidget::FragmentWidget()
    : QDialog()
{
    QBoxLayout* lt = new QBoxLayout(QBoxLayout::TopToBottom);
    QPushButton* process = new QPushButton("Ok");

    this->setLayout(lt);
    lt->addWidget(process);
    connect(process, &QPushButton::pressed, this, &FragmentWidget::accept);
}


void ImageToFragment::setParameters(QVector<QVariant> p)
{
    Q_UNUSED(p);
}

QVector<QVariant> ImageToFragment::getParameters() const
{
    QVector<QVariant> v;
    v.clear();
    return v;
}
