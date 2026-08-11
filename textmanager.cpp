#include "textmanager.h"

#include <QFile>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

TextManager::TextManager() {}


void TextManager::WriteInFile(QString text) {

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    dir.mkpath(path);

    qDebug() << path;

    QFile f(path +"/text.txt");

    bool isOpen = f.open(QIODevice::WriteOnly);

    if(!isOpen) {
        qDebug() << "Файл не был открыт";
    }

    f.write(text.toUtf8());
    f.close();
}