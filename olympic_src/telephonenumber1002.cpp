#include <QDebug>
#include <QStringList>
#include <map>
#include <vector>
#include "telephonenumber1002.h"

void TelephoneNumber1002::createMaps()
{
    number_map[1] = "ij";
    number_map[2] = "abc";
    number_map[3] = "def";
    number_map[4] = "gh";
    number_map[5] = "kl";
    number_map[6] = "mn";
    number_map[7] = "prs";
    number_map[8] = "tuv";
    number_map[9] = "wxy";
    number_map[0] = "ogz";
    for(auto it = number_map.begin(); it!=number_map.end(); it++)
    {
        QString number = it.value();
        for(int i=0; i < number.size(); i++)
            inv_number_map[QString(number[i])] = it.key();
    }
}

QString TelephoneNumber1002::word2number(QString word)
{
    QString ret;
    for(int i=0; i < word.size(); i++)
    {
        if( inv_number_map.find(QString( word[i] ) )!=inv_number_map.end() )
        {
            ret+=QString::number( inv_number_map[QString( word[i] ) ] );
        }
    }
    return ret;
}

bool wordsIntersects(QString& phrase, QString& word1, QString& word2)
{
    bool b1;
    if( phrase.indexOf(word1) == phrase.indexOf(word2) )
        return false;
    if( phrase.indexOf(word1) < phrase.indexOf(word2) )
    {
        b1 = (phrase.indexOf(word1) + word1.size()) < phrase.indexOf(word2);
    }
    else
    {
        b1 = (phrase.indexOf(word2) + word2.size()) < phrase.indexOf(word1);
    }
    return b1;

}

void outSeq(std::vector<QString>& sequence)
{
    for(auto it = sequence.begin(); it!=sequence.end(); it++)
        qDebug() << (*it);
    qDebug() << "----------------------";
}

bool checkSeq(QString orignumber, std::vector<QString> sequence)
{
    int size=0;
    for(auto it = sequence.begin(); it!=sequence.end(); it++)
    {
        size+=(*it).size();
    }
    return orignumber.size() == size;
}

bool TelephoneNumber1002::cutNumber(QString orignumber, QString number, std::vector<QString>& matchedWords, std::vector<QString> sequence)
{
    bool bMatch=false;
    for(auto it = matchedWords.begin(); it!=matchedWords.end(); it++)
    {
        int n1 = number.indexOf(word2number((*it)));
        if(n1!=-1)
        {
            if(word2number((*it)) == number)
              bMatch = true;
            sequence.push_back((*it));

            QString subword1 = number.mid(0,n1);
            QString subword2 = number.mid( n1+(*it).size(),
                                           number.size()-n1-(*it).size());
            bool r1,r2;
            if( subword1.size()!=0 )
                r1 = cutNumber(orignumber, subword1, matchedWords, sequence);
            if( subword2.size()!=0 )
                r2 = cutNumber(orignumber, subword2, matchedWords, sequence);
            if( (r1  ||  r2) && checkSeq(orignumber, sequence) )
            {
                outSeq(sequence);
                //return;
            }


        }

    }
    return bMatch;
}

TelephoneNumber1002::TelephoneNumber1002()
{
    QStringList list;

    createMaps();

    QString input;
    input = "7325189087 " \
    "5 "\
    "it "\
    "your "\
    "reality "\
    "real "\
    "our "\
    "4294967296 "\
    "5 "\
    "it "\
    "your "\
    "reality "\
    "real "\
    "our "\
    "-1";

    list = input.split(" ");
    QString number = list[0];
    QStringList words;
    for(int i=0; i < list[1].toInt(); i++)
        words.append(list[i+2]);

    std::vector<QString> matchedWords;
    for(int i=0; i < list[1].toInt(); i++)
    {
        QString n = word2number(words[i]);
        if( number.indexOf(n)!=-1 )
        {
            matchedWords.push_back(words[i]);
            qDebug() << " " << words[i] << " " << n;
        }
    }
    std::sort(matchedWords.begin(), matchedWords.end(),
        [](const QString&  a, const QString& b) -> bool
    {
         return a.size() > b.size();
    });

    qDebug() << "------------";
/*    matchedWords[0];
    //---- 1 variant
    int len = number.size();
    for(auto it2 = matchedWords.begin(); it2!=matchedWords.end(); it2++)
    for(auto it = matchedWords.begin(); it!=matchedWords.end(); it++)
    {
        int d = len - (*it2).size() - (*it).size();
        if( it2 < it ) continue;

        if( d == 0 && !wordsIntersects(number,
                                       word2number((*it2)),
                                       word2number((*it)))  )
        {
            qDebug() << *it << " " << *it2;
        }

    }
*/
    //---- 2 variant
    std::vector<QString> sequence;
    cutNumber(number, number, matchedWords, sequence);




}
