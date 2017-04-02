/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     qssloader.cpp
**  @brief    launch widget
**  @details  show launch progress and display some messages
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "qssloader.h"
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QApplication>
#include <QWidget>

QStringList QssLoader::findAllQss(const QString &path)
{
    QStringList list;

    QDir dir(path);
    if(!dir.exists())
        return list;

    QStringList filters;
    filters << QString("*.qss");

    QDirIterator dirIter(path, filters,
                         QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot,
                         QDirIterator::Subdirectories);

    while(dirIter.hasNext())
    {
        dirIter.next();
        QFileInfo info = dirIter.fileInfo();
        list << info.absoluteFilePath();
    }

    return list;
}

bool QssLoader::loadQss(const QString &name)
{
    QFile file(name);
    if(!file.exists())
        return false;

    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    qApp->setStyleSheet(data.constData());

    return true;
}

bool QssLoader::loadQss(QWidget *widget, const QString &name)
{
    QFile file(name);
    if(!file.exists())
        return false;

    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    widget->setStyleSheet(data.constData());

    return true;
}
