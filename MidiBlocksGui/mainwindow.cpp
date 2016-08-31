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

#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QtWidgets/QGraphicsView>
#include "controlblock.h"
#include <QDebug>

#include <QPluginLoader>
#include <QDir>
#include <QtWidgets/QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_view = new QGraphicsView();
    this->setCentralWidget(m_view);
    m_view->setAcceptDrops(true);

    m_scene = new ControlGraphicsScene();
    m_view->setScene(m_scene);

    ui->lv_plugins->setModel(&m_pluginModel);

    loadPlugins();
}

MainWindow::~MainWindow()
{
    this->setCentralWidget(NULL);

    m_view->setScene(NULL);
    delete m_view;

    delete m_scene;

    delete ui;
}

void MainWindow::loadPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances())
    {
        addPlugin(plugin, "");
    }

    QDir pluginsDir = QDir(QApplication::applicationDirPath());
    pluginsDir.cd("/usr/local/share/MidiBlocks/plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        QObject *plugin = loader.instance();
        if (plugin) {
            addPlugin(plugin, pluginsDir.absoluteFilePath(fileName));
        }
    }
}

void MainWindow::addPlugin(QObject* plugin, QString filePath)
{
    ControlBlock *block = qobject_cast<ControlBlock*>(plugin);
    if (block)
    {
        m_pluginModel.addPlugin(block->getName(), filePath);
    }
}
