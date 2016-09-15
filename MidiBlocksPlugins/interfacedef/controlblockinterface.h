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

#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QtPlugin>
#include <QString>
#include <QtWidgets/QWidget>

class iControlBlock : public QObject
{
    Q_OBJECT

public:
    virtual ~iControlBlock() {}
    
    virtual QString getName()=0;
    virtual QString getGroupName()=0;
    virtual QWidget* getEditorWidget()=0;
    virtual iControlBlock* createDefaultBlock()=0;
    
protected:
    
};



#endif // CONTROLBLOCK_H

