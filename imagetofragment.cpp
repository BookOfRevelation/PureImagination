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

    PureCore::condition = new PaintCondition(PureCore::conditionPoints);
    PureCore::condition->init();

}

FragmentWidget::FragmentWidget()
    : QDialog()
{
    QBoxLayout* lt = new QBoxLayout(QBoxLayout::TopToBottom);

    selectionSS = new SlideSpiner("Selection size", "px", 1, 1, 100);
    selectionSS->setToMiddle();

    view = new FragmentView;

    view->setScene(new QGraphicsScene());

    view->selection = view->scene()->addRect(0,0,1,1);
    view->selection->setPen(QPen(Qt::black));

    QPushButton* process = new QPushButton("Ok");

    view->setSelSize(selectionSS->getValue());

    this->setLayout(lt);

    QBoxLayout* validLt = new QBoxLayout(QBoxLayout::LeftToRight);
    validLt->addWidget(selectionSS);
    validLt->addWidget(process);

    lt->addLayout(validLt);
    lt->addWidget(view);
    connect(process, &QPushButton::pressed, this, [this]()
    {
        PureCore::conditionPoints = this->view->points;

        this->accept();
    });
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
    buttonState = Qt::NoButton;
}

void FragmentView::mouseMoveEvent(QMouseEvent *e)
{
    selection->setPos(e->pos().x(), e->pos().y());
    selection->setRect(0, 0, size, size);
    selection->setZValue(10);

    activePixel(e);

}

void FragmentView::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    buttonState = Qt::NoButton;
}

void FragmentView::mousePressEvent(QMouseEvent *e)
{
    buttonState = e->button();
     activePixel(e);
}

void FragmentView::activePixel(QMouseEvent *e)
{
    QPoint p = e->pos();
    QImage img = item->pixmap().toImage();

    for(int c = p.x() ; c < p.x() + size ; ++c)
    {
        for(int j = p.y() ; j < p.y() + size ; ++j)
        {
            if(c>=0 && j>=0 && c < img.width() &&  j < img.height())
            {
               if(
                   (points[c][j] == true && buttonState == Qt::RightButton) ||
                   (points[c][j] == false && buttonState == Qt::LeftButton)
                )
               {
                   points[c][j] = !points[c][j];
                   QColor pc = img.pixelColor(c, j);
                   pc.setRed(255-pc.red());
                   pc.setGreen(255-pc.green());
                   pc.setBlue(255-pc.blue());

                   img.setPixelColor(c, j, pc);
               }

            }
        }
    }


    item->setPixmap(QPixmap::fromImage(img));
}

void FragmentView::init()
{
    QImage img = static_cast<PureImage*>(PureCore::currentData)->getImage(0);

    this->setFixedSize(img.width(), img.height());

    item = this->scene()->addPixmap(QPixmap::fromImage(img));

    for(int i = 0 ; i < img.width() ; ++i)
    {
        QVector<bool> line;
        line.clear();
        for(int j = 0 ; j < img.height() ; ++j)
        {
            line.push_back(false);
        }
        points.push_back(line);
    }
}
