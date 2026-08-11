#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <qstring.h>

class TextManager
{
public:
    TextManager();
    static void WriteInFile(QString title, QString text);
    static QStringList getFiles();
};

#endif // TEXTMANAGER_H
