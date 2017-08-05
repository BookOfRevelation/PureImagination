#include "puretreeitem.h"

PureTreeItem::PureTreeItem()
    : QTreeWidgetItem(), effect(nullptr)
{

}


PureTreeItem::~PureTreeItem()
{
}

void PureTreeItem::setEffect(PureEffect *e)
{
    effect = e;
}

PureEffect* PureTreeItem::getEffect()
{
    return effect;
}
