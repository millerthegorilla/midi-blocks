/*
    Copyright (C) 2013  Adam Nash

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  */

#include "chordbankblock.h"
#include "ui_chordbankblockeditor.h"
#include "chorditemdelegate.h"
#include <QDebug>

ChordBankBlock::ChordBankBlock(QObject *parent) :
    editorUi(new Ui::ChordBankBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    editorUi->tv_chords->setModel(&m_model);

    editorUi->tv_chords->setItemDelegateForColumn(0, new ChordItemDelegate(this));

    editorUi->verticalLayout->insertWidget(0, &m_chordEditor);

    connect(editorUi->pb_add, SIGNAL(clicked()),
            this, SLOT(addChord()));
    connect(editorUi->pb_remove, SIGNAL(clicked()),
            this, SLOT(removeChord()));

    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QChordBankBlock" FILE "chordbankblock.json")
}

ChordBankBlock::~ChordBankBlock()
{
    delete editorUi;
    delete editor;
}

QString ChordBankBlock::getName()
{
    return "Chord Bank Block";
}

QString ChordBankBlock::getGroupName()
{
    return "Chord Blocks";
}

QWidget* ChordBankBlock::getEditorWidget()
{
    return editor;
}

ControlBlock* ChordBankBlock::createDefaultBlock()
{
    return new ChordBankBlock();
}

void ChordBankBlock::receiveBeat(QByteArray message)
{
    Q_UNUSED(message)

    //take off all previous notes
    if (!m_notes.isEmpty())
    {
        foreach(QByteArray note, m_notes)
        {
            note[0] = 128;
            sendChord(note);
        }
        m_notes.clear();
    }

    m_model.incrementBeat();
    QList<QVariant> notes = m_model.getChordForBeat();

    foreach(QVariant note, notes)
    {
        QByteArray noteOn;
        noteOn.push_back(static_cast<char>(144));
        noteOn.push_back(static_cast<char>(note.toInt()));
        noteOn.push_back(static_cast<char>(100));

        m_notes.push_back(noteOn);
        sendChord(noteOn);
    }
}

//void ChordBankBlock::receiveToggle_Write_Mode(QByteArray message)
//{
//    //TODO: engage chord writing mode
//}

//void ChordBankBlock::receiveWrite_Input(QByteArray message)
//{
//    //TODO: write the chord if in chord writing mode
//}

void ChordBankBlock::addChord()
{
    if (m_model.insertRows(m_model.rowCount(QModelIndex()), 1, QModelIndex()))
    {
        m_model.setData(m_model.index(m_model.rowCount(QModelIndex())-1, 0),
                        m_chordEditor.getValues(),
                        Qt::EditRole);
    }
}

void ChordBankBlock::removeChord()
{
    foreach (QModelIndex index, editorUi->tv_chords->selectionModel()->selectedRows())
    {
        m_model.removeRows(index.row(), 1, QModelIndex());
    }
}

//Q_PLUGIN_METADATA(chordbankblockplugin, ChordBankBlock)

