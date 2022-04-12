// http://acm.timus.ru/problem.aspx?space=1&num=1545

#include <QStringList>
#include <QDebug>
#include "ieroglif1545.h"

Ieroglif1545::Ieroglif1545()
{
    QStringList input;
    input.append("6");
    input.append("na");
    input.append("no");
    input.append("ni");
    input.append("ki");
    input.append("ka");
    input.append("ku");
    input.append("k");
    for(int i=1; i < input[0].toInt()+1; i++)
    {
        addWord(input[i]);
    }
    QString searchStr = input.last();
    Letter* l = findLetter(searchStr[0], root.children);
    QString word=*l;
    printWords(l, word);
}

Letter* Ieroglif1545::findLetter(QChar l, std::vector<Letter*>& letters)
{
    for(auto it=letters.begin(); it!=letters.end(); it++)
    {
        if( *(*it) == l )
            return (*it);
    }
    return 0;
}

void Ieroglif1545::printWords(Letter* l, QString word)
{
    if(l->children.size() == 0)
    {
        qDebug() << word;
    }
    else
    {
        for(auto it=l->children.begin(); it!=l->children.end(); it++)
        {
            //word+=*(*it);
            printWords((*it), word+*(*it));
        }
    }
}

void Ieroglif1545::addWord(QString w)
{
    Letter* cur_letter = &root;
    for(int i=0; i < w.size(); i++)
    {
        Letter* letter = findLetter(w[i], cur_letter->children);
        if( letter == 0 ) // create new letter
        {
            Letter* new_letter = new Letter(w[i]);
            cur_letter->children.push_back(new_letter);
            cur_letter = new_letter;
        }
        else
          cur_letter = letter;
    }
}
