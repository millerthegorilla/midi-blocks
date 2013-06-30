#include "%ProjectName:l%.%CppHeaderSuffix%"
#include "ui_%ProjectName:l%editor.h"

%ProjectName%::%ProjectName%(QObject *parent) :
    editorUi(new Ui::%ProjectName%Editor)
{
    if (parent)
    {
        setParent(parent);
    }

    editor = new QWidget();
    editorUi->setupUi(editor);
}

%ProjectName%::~%ProjectName%()
{
    delete editorUi;
    delete editor;
}

QString %ProjectName%::getName()
{
    return "%ProjectName%";
}

QString %ProjectName%::getGroupName()
{
    return "My Control Blocks";
}

QWidget* %ProjectName%::getEditorWidget()
{
    return editor;
}

ControlBlock* %ProjectName%::createDefaultBlock()
{
    return new %ProjectName%();
}

Q_EXPORT_PLUGIN2(%ProjectName:l%plugin, %ProjectName%)
