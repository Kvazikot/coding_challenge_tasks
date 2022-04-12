#include <QStringList>
#include <QDebug>
#include "codewords1007.h"

CodeWords1007::CodeWords1007(QString input)
{
    QStringList list = input.split(",");
    N = list[0].toInt();
    list.removeAt(0);
    words = list;
    foreach(QString w, words)
    {
        for(int i=0; i < w.size(); i++)
            if( w[i]!='1' && w[i]!='0')
            {
                qDebug() << w << " check input!";
                continue;
            }
        qDebug() << w << " " << correctWord(w);
    }
}

QString CodeWords1007::correctWord(QString word)
{
    QString w = word;
    while( 1 )
    {
        int pos = rand()%N;
        w = word;
        if( word.size() == N )
        {
            if( w[pos] == '1')
                w[pos] = '0';

        }
        if( word.size() < N )
            w.insert(pos,QString::number(rand()%2));
        if( word.size() > N )
            w.remove(pos,1);
        if((checkSum(w) % (N + 1))==0)
            break;
    }
    return w;
}

int CodeWords1007::checkSum(QString word)
{
    int sum=0;
    for(int i=0; i < word.size(); i++)
    {
        if( word[i] == '1' )
           sum+=i+1;
    }
    return sum;
}
