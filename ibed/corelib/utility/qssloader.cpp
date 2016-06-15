/************************************************************
 * Copyright (C), 2016-2017, Intellicare. Co., Ltd.
 * FileName: qssloader.cpp
 * Author: HuangYang
 * Description:     // 模块描述
 * Version:         // 版本信息
 * History:
 *     HuangYang    2016/4/9     1.0     build this moudle
***********************************************************/
#include "qssloader.h"
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QApplication>

QssLoader::QssLoader() :
    m_curQss(QString())
{

}

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
    file.readAll();

    qApp->setStyleSheet(name);

    emit qssChanged(name);

    return true;
}
