#include "textmanager.h"

#include <QFile>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

TextManager::TextManager() {}


void TextManager::WriteInFile(QString title, QString text) {

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    dir.mkpath(path);

    QFile f(path +"/" + title + ".txt");

    bool isOpen = f.open(QIODevice::WriteOnly);

    if(!isOpen) {
        qDebug() << "Файл не был открыт";
    }

    f.write(text.toUtf8());
    f.close();
}



QStringList TextManager::getFiles() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    return dir.entryList(QDir::Files);
}