#ifndef PURETREEITEM_H
#define PURETREEITEM_H
#include <QTreeWidgetItem>
#include "pureeffect.h"

class PureTreeItem : public QTreeWidgetItem
{
public:
    PureTreeItem();
    virtual ~PureTreeItem();

    void setEffect(PureEffect* e);
    PureEffect* getEffect();


private:

    PureEffect* effect;
};

#endif // PURETREEITEM_H
