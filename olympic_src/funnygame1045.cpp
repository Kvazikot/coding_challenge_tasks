#include <QDebug>
#include <QStringList>
#include "funnygame1045.h"

char FunnyGame1045::dfs(int v, int e, bool found, char player)
{

    if(player == WHITE)
        player = BLACK;
    else
        player = WHITE;

    color[v] = player;
    //qDebug() << v << " " << QString::number(player);

    if( v == e)
        found = true;

    bool hasPoint = false;
    for(int i=0; i < g[v].size(); i++)
    {
        if( color[g[v][i]] == GRAY)
        {
            hasPoint = true;
            dfs(g[v][i],e,found,player);
        }
    }

    if(found && !hasPoint)
    {
        win_player = player - 1;
    }
}

FunnyGame1045::FunnyGame1045(QString input)
{
    QStringList lines = input.split(",");
    QStringList parts = lines[0].split(" ");
    int n = parts[0].toInt();
    int start = parts[1].toInt();

    //create grapth
    for(int i=0; i <= n; i++)
    {
        g.push_back(std::vector<int>());
        color.push_back(0);
    }

    for(int i=1; i < lines.size(); i++)
    {
        parts = lines[i].split(" ");
        int n1 = parts[0].toInt();
        int n2 = parts[1].toInt();
        g[n1].push_back(n2);
    }
    //по всем аэропортам
    qDebug() << "starting point " << start;
    for(int i=1; i <= n; i++)
    {
        dfs(start,i,0,BLACK);
        for(int i=0; i <= n; i++)
            color[i]=0;
        QString word;
        if(win_player) word = "win"; else  word = "lose";
        qDebug() << "First player " << word << " flying to airport " << i;
    }
}
