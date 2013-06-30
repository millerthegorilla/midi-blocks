#ifndef %ProjectName:u%_H
#define %ProjectName:u%_H

#include "controlblock.%CppHeaderSuffix%"
#include <QWidget>

namespace Ui {
class %ProjectName%Editor;
}

class %ProjectName% : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)

public:
    explicit %ProjectName%(QObject* parent = 0);
    ~%ProjectName%();

    QString getName();
    QString getGroupName();

    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock();

signals:
    //Prefix visible outputs with "send"

public slots:
    //Prefix visible inputs with "receive"

private:
    Ui::%ProjectName%Editor* editorUi;
    QWidget* editor;
};

#endif // %ProjectName:u%_H

