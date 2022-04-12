#include "order_havoc1921.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <time.h>
#include <map>

order_havoc1921::order_havoc1921()
{
    QString input = "4 4 4 4";
    ParseInput(input);
    InitCells(n,m);
    Generate();


}

void order_havoc1921::Print()
{
    for(int i=0; i < n; i++)
    {
        QString str;
        for(int j=0; j < m; j++)
        {
            str+=cells[i][j];
        }
        qDebug() << str;
    }
}

void order_havoc1921::InitCells(int n, int m)
{
    cells = new char*[n];
    for(int i=0; i < n; i++)
    {
       cells[i] = new char[m];
       for(int j=0; j < m; j++)
       {
          cells[i][j] = '.';
       }

    }
}

void order_havoc1921::ClearCells(int n, int m)
{
    for(int i=0; i < n; i++)
    {
       for(int j=0; j < m; j++)
       {
          cells[i][j] = '.';
       }
    }
}

char order_havoc1921::makeRandChar(int k)
{
    time_t t;

    char c = 'A' + rand()%k;
    return c;
}

bool order_havoc1921::CheckDiogonal()
{
    std::map<char,std::vector<int>> cmap;
    if(m!=n) return true;
    for(int i=0; i < n; i++)
    {
        int j = i;
        if(cmap.find(cells[i][j]) == cmap.end())
        {
            cmap[cells[i][j]] = std::vector<int>();
            cmap[cells[i][j]].push_back(j);
        }
        else {

            if((j - cmap[cells[i][j]].back())==1)
            {
               cmap[cells[i][j]].push_back(j);
               if( cmap[cells[i][j]].size() == l)
                   return false;
            }
            else {
                //cmap.erase(cmap.find(cells[i][j]));
                cmap[cells[i][j]].clear();
                cmap[cells[i][j]].push_back(j);
            }
        }
    }
    for(int i=0; i < n; i++)
    {
        int j = n - i;
        if(cmap.find(cells[i][j]) == cmap.end())
        {
            cmap[cells[i][j]] = std::vector<int>();
            cmap[cells[i][j]].push_back(j);
        }
        else {

            if((j - cmap[cells[i][j]].back())==1)
            {
               cmap[cells[i][j]].push_back(j);
               if( cmap[cells[i][j]].size() == l)
                   return false;
            }
            else {
                //cmap.erase(cmap.find(cells[i][j]));
                cmap[cells[i][j]].clear();
                cmap[cells[i][j]].push_back(j);
            }
        }
    }
    return true;
}

bool order_havoc1921::CheckRows()
{
    std::map<char,std::vector<int>> cmap;
    for(int i=0; i < n; i++)
    {
       cmap.clear();
       for(int j=0; j < m; j++)
       {
          if(cmap.find(cells[i][j]) == cmap.end())
          {
              cmap[cells[i][j]] = std::vector<int>();
              cmap[cells[i][j]].push_back(j);
          }
          else {

              if((j - cmap[cells[i][j]].back())==1)
              {
                 cmap[cells[i][j]].push_back(j);
                 if( cmap[cells[i][j]].size() == l)
                     return false;
              }
              else {
                  //cmap.erase(cmap.find(cells[i][j]));
                  cmap[cells[i][j]].clear();
                  cmap[cells[i][j]].push_back(j);
              }
          }
       }


    }
    return true;
}

bool order_havoc1921::CheckCols()
{
    std::map<char,std::vector<int>> cmap;

    for(int j=0; j < m; j++)
    {
       cmap.clear();
       for(int i=0; i < n; i++)
       {
          if(cmap.find(cells[i][j]) == cmap.end())
          {
              cmap[cells[i][j]] = std::vector<int>();
              cmap[cells[i][j]].push_back(i);
          }
          else {


              if((i - cmap[cells[i][j]].back())==1)
              {
                 cmap[cells[i][j]].push_back(i);
                 if( cmap[cells[i][j]].size() == l)
                     return false;
              }
              else {
                  //cmap.erase(cmap.find(cells[i][j]));
                  cmap[cells[i][j]].clear();
                  cmap[cells[i][j]].push_back(j);
              }


          }
       }

    }
    return true;
}

void order_havoc1921::Generate()
{
    bool ok=false;
    int count=0;
    time_t t;
    srand(time(&t));

    while(!ok )
    {
        ClearCells(n,m);
        // write string to rand row
        char c = makeRandChar(k);

        int i = rand()%n;
        for(int j=0; j < l-1; j++)
            cells[j][i] = c;
        // put to other cells random chars
        for(int i=0; i < n; i++)
           for(int j=0; j < m; j++)
              if(cells[i][j] == '.')
                  cells[i][j] = makeRandChar(k);

        //check
        if( CheckRows() == true)
          if( CheckCols() == true)
              ok = CheckDiogonal();
        count++;


       // ok = true;


    }
    Print();
    qDebug() << "iterations " << count;

}

void order_havoc1921::ParseInput(QString input)
{
    QStringList list = input.split(" ");
    n = list[0].toInt();
    m = list[1].toInt();
    k = list[2].toInt();
    l = list[3].toInt();

}
