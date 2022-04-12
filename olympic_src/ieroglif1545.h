#ifndef IEROGLIF1545_H
#define IEROGLIF1545_H

#include <QString>
#include <vector>

class Letter : public QChar
{
public:
    Letter(){}
    Letter(QChar s) :
     QChar(s)
    {
    }

    std::vector<Letter*> children;
};

class Ieroglif1545
{
public:
    Ieroglif1545();
    Letter* findLetter(QChar l, std::vector<Letter*>& letters);
    void addWord(QString w);
    void printWords(Letter* l, QString word);
    Letter root;
};

#endif // IEROGLIF1545_H
