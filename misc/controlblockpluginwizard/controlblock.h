#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QtPlugin>
#include <QString>
#include <QWidget>

/*!

\class ControlBlock controlblock.h
\brief Abstract interface for control block plugins

Implement this interface in order to create a control block that can be loaded by
the program.  Qt signals with names that start with "send" will be the outputs,
and Qt slots with names that start with "receive" will be the inputs.

Input slots and output signals should have a single QByteArray as their parameter.

\see ControlGraphicsScene ControlBlockGraphicsItem

*/
class ControlBlock : public QObject
{
public:
    virtual ~ControlBlock() {}

    virtual QString getName()=0;
    virtual QString getGroupName()=0;
    virtual QWidget* getEditorWidget()=0;
    virtual ControlBlock* createDefaultBlock()=0;

protected:

};

Q_DECLARE_INTERFACE(ControlBlock,
                     "org.midiblocks.ControlBlock/1.0")

#endif // CONTROLBLOCK_H

