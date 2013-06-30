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

#ifndef CHORDEDITOR_H
#define CHORDEDITOR_H

#include <QWidget>
#include <QMap>

namespace Ui {
class ChordEditor;
}

class ChordEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChordEditor(QWidget *parent = 0);
    ~ChordEditor();

    void setValues(QList<QVariant> values);
    QList<QVariant> getValues() const;

private slots:
    void adjustToParameters();
    
private:
    Ui::ChordEditor *ui;

    QList<QVariant> m_values;

    QMap<QString, char> m_baseNoteMap;
    QMap<QString, QList<char> > m_chordNoteMap;
};

#endif // CHORDEDITOR_H
