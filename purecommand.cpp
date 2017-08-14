#include "purecommand.h"
#include <QDebug>
#include "purecore.h"

PureCommand::PureCommand(CommandParameters* cp, QUndoStack* p)
    : QUndoCommand(), commandParameter(cp), parent(p)
{

}

PureCommand::~PureCommand()
{
    delete commandParameter;
}

void PureCommand::undo()
{
    commandParameter->scene->removeEffect(commandParameter->effect);
    int index = parent->index();
    if(index > 1)
    {
        const PureCommand* curcom = static_cast<const PureCommand*>(parent->command(index-1));

        commandParameter->currentEffect = curcom->commandParameter->effect;
        PureCore::currentOutput = curcom->commandParameter->currentEffect->getOutputType();
    }
    else
    {
        commandParameter->currentEffect = nullptr;
        PureCore::currentOutput = PureCore::NoType;
    }
}

void PureCommand::redo()
{
    commandParameter->scene->addEffect(commandParameter->effect);
    commandParameter->currentEffect = commandParameter->effect;

    PureCore::currentOutput = commandParameter->currentEffect->getOutputType();
}

