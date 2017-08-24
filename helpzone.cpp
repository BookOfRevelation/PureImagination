#include "helpzone.h"
#include "purecore.h"
HelpZone::HelpZone(QWidget *parent) : QWidget(parent)
{
    mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    widget = new QWidget;
    QBoxLayout* ltw = new QBoxLayout(QBoxLayout::TopToBottom);
    widget->setLayout(ltw);
    ttl = new QLabel("Aide");
    desc = new QLabel("Sélectionnez un effet de la liste pour afficher l'aide.");
    ltw->addWidget(ttl, 0, Qt::AlignCenter);
    ltw->addWidget(desc);

    this->setLayout(mainLt);
    mainLt->addWidget(widget);

    widget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding));
}


void HelpZone::setWidget(const QString& t, const QString& d)
{
    ttl->setText(t);
    //desc->setText(d);
    desc->setPixmap(QPixmap(QString(":/res/examples/%1.jpg").arg(d)));

}
