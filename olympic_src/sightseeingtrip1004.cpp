#include <QStringList>
#include <map>
#include <QDebug>
#include "sightseeingtrip1004.h"

void SightseeingTrip1004::printPath(std::vector<int> path)
{
    QString out;
    for(int i=0; i < path.size(); i++)
        out+=QString::number(path[i]+1)+",";
    qDebug() << out;
}

int SightseeingTrip1004::pathHash(std::vector<int> path)
{
    QString out;
    for(int i=0; i < path.size(); i++)
        out+=QString::number(path[i]);
    return out.toInt();
}

void SightseeingTrip1004::dfs(int v, std::vector<int> path)
{
    color[v] = BLACK;
    path.push_back(v);
    for(int i=0; i < g[v].size(); i++)
    {
        if( color[g[v][i]] == BLACK) //found a cycle
        {
            if( hashes.find(pathHash(path)) == hashes.end())
            {
                paths.push_back(path);
                hashes[pathHash(path)] = 1;
            }
        }
        if( color[g[v][i]] == WHITE)
            dfs(g[v][i],path);
    }

}

int  SightseeingTrip1004::getPathDist(std::vector<int> path)
{
    int sum=0;
    for(int i=0; i < path.size()-1; i++)
    {
        int n1 = path[i];
        int n2 = path[i+1];
        sum+=dist[std::make_pair(n1,n2)];
    }
    return sum;

}

void SightseeingTrip1004::selectPath()
{
    std::sort(paths.begin(), paths.end(),
              [](const std::vector<int>  a, std::vector<int>  b) -> bool
    {
              return a.size() > b.size();
    });
    if(paths.size())
    {
        if(paths[0].size() > 1)
        {
            //выбираем самые разветвленные пути
            paths.erase(std::remove_if(paths.begin(), paths.end(),
                                       [&](const std::vector<int>  a)
            {
                if( a.size() < paths[0].size())
                    return true;
                else
                    return false;
            }),paths.end());
            // выбираем самый короткий
            std::sort(paths.begin(), paths.end(),
                [&](const std::vector<int>  a, std::vector<int>  b) -> bool
            {
              return getPathDist(a) > getPathDist(b);
            });
            printPath(paths[0]);
        }
        else
           qDebug() << "No solution";
    }
        else
            qDebug() << "No solution";


//std::copy_if(paths.begin(), paths.end(), paths2.end(), compare_paths());

//

}


void SightseeingTrip1004::processGrapth()
{
    for(int i=0; i < g.size(); i++)
    {
        std::vector<int> path;
        if( color[i] == WHITE )
            dfs(i,path);
    }
    selectPath();
}


SightseeingTrip1004::SightseeingTrip1004(QString input)
{
    QStringList lines = input.split(",");
    int Nvert=0,Nedges=0;
    for(int i=0; i < lines.size(); i++)
    {
        QStringList parts = lines[i].split(" ");
        if( parts.size() == 2 )
        {
            processGrapth();
            Clear();
            Nvert = parts[0].toInt();
            Nedges = parts[1].toInt();
            for(int j=0; j < Nvert; j++)
            {
                g.push_back(std::vector<int>());
                color.push_back(0);
            }
        }
        if( parts.size() == 3 )
        {
            int n1 = parts[0].toInt()-1;
            int n2 = parts[1].toInt()-1;
            dist[std::make_pair(n1, n2)] = parts[2].toInt();
            g[n1].push_back(n2);
            g[n2].push_back(n1);
        }
        if( parts.size() == 1 )
        {
            if( parts[0] == "-1" )
                processGrapth();

        }


    }

}

void SightseeingTrip1004::Clear()
{
    g.clear();
    dist.clear();
    color.clear();
    paths.clear();
}
