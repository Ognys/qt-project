#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <qstring.h>

class TextManager
{
public:
    TextManager();
    static void WriteInFile(QString text);
};

#endif // TEXTMANAGER_H
