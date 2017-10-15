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
    widget->init();
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

    PureCore::condition = new ThresholdCondition(255, false);
    PureCore::condition->init();

}

FragmentWidget::FragmentWidget()
    : QDialog()
{
    QBoxLayout* lt = new QBoxLayout(QBoxLayout::TopToBottom);

    selectionSS = new SlideSpiner("Selection size", "px", 1, 1, 100);

    view = new FragmentView;
    view->setScene(new QGraphicsScene());
    view->selection = view->scene()->addRect(0,0,1,1);
    view->selection->setPen(QPen(Qt::black));
    QPushButton* process = new QPushButton("Ok");

    this->setLayout(lt);
    lt->addWidget(selectionSS);
    lt->addWidget(view);
    lt->addWidget(process);
    connect(process, &QPushButton::pressed, this, &FragmentWidget::accept);
    connect(selectionSS, &SlideSpiner::valueChanged, view, &FragmentView::setSelSize);
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


FragmentView::FragmentView()
    : QGraphicsView()
{
    setMouseTracking(true);
}

void FragmentView::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<e->pos();
    selection->setPos(e->pos().x(), e->pos().y());
    selection->setRect(0, 0, size, size);
    selection->setZValue(10);
}

void FragmentView::init()
{
    QImage img = static_cast<PureImage*>(PureCore::currentData)->getImage(0);

    this->setFixedSize(img.width(), img.height());

    this->scene()->addPixmap(QPixmap::fromImage(img));
}
