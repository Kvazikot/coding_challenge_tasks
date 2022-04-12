#ifndef TELEPHONENUMBER1002_H
#define TELEPHONENUMBER1002_H

#include <QMap>
#include <QString>

class TelephoneNumber1002
{
    QMap<int, QString> number_map;
    QMap<QString, int> inv_number_map;
public:
    TelephoneNumber1002();
    QString word2number(QString word);
    bool cutNumber(QString orignumber, QString number, std::vector<QString>& matchedWords, std::vector<QString> sequence);
    void createMaps();
};

#endif // TELEPHONENUMBER1002_H
