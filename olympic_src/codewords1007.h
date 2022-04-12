#ifndef CODEWORDS1007_H
#define CODEWORDS1007_H

#include <QString>
#include <QStringList>

class CodeWords1007
{
public:
    int N;
    QStringList words;
    CodeWords1007(QString input);
    int checkSum(QString word);
    QString correctWord(QString word);
};

#endif // CODEWORDS1007_H
