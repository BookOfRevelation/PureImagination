#ifndef PURECOMMAND_H
#define PURECOMMAND_H
#include <QUndoCommand>
#include "commandparameters.h"
class PureCommand : public QUndoCommand
{
public:
    PureCommand(CommandParameters* cp, QUndoStack* p);

    virtual void undo();
    virtual void redo();

    ~PureCommand();

private:
    CommandParameters* commandParameter;
    QUndoStack* parent;

};

#endif // PURECOMMAND_H
