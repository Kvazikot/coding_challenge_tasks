#include <QString>
#include <QDebug>
#include <QStringList>
#include "spellchecker1038.h"

int checkWord(QString word)
{
    int n_errors=0;
    int n_skip=1;
    if(word.size() == 0) return 0;

    for(int i=0; i < word.size(); i++)
      if( !word[i].isLetter() )
          n_skip++;

    for(int i=n_skip; i < word.size(); i++)
      if( word[i].isUpper() )
          n_errors++;
    return n_errors;
}

SpellChecker1038::SpellChecker1038()
{

    //The first letter in a sentence is small.
    //A capital letter is not the first letter in a word.
    int n_errors=0;
    QString s = "This sentence iz correkt! -It Has,No mista;.Kes et oll." \
                "But there are two BIG mistakes in this one!" \
                "and here is one more.";
    QStringList sentenses = s.split(QRegExp("[!.]"));
    for(int i=0; i < sentenses.size(); i++)
        if( sentenses[i][0].isLower() )
            n_errors++;
    s = s.replace(","," ");
    s = s.replace("."," ");
    s = s.replace(";"," ");
    QStringList words = s.split(" ");

    for(int i=0; i < words.size(); i++)
    {
            n_errors+=checkWord(words[i]);
            if( checkWord(words[i])!=0 )
              qDebug() << words[i];
    }
    qDebug() << n_errors;

}
