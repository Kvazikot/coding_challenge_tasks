#include <QDebug>
#include "deltawave1302.h"

void out_arr( std::vector<int> arr)
{
    QString s;
    for(auto i=arr.begin(); i!=arr.end(); i++)
    {
        s+=QString::number( (*i) ) + ",";
    }
    qDebug() << s;
}

void Deltawave1302::add_edges( std::vector<int> prev_arr, std::vector<int> arr)
{
    // смежные ребра
    for(int i=0; i < arr.size()-1; i++)
    {
       // qDebug() << "rebro " << arr[i] << "-" << arr[i+1];
        g[arr[i]].push_back(arr[i+1]);
        g[arr[i+1]].push_back(arr[i]);
    }

    // ребро вверх - вниз
    for(int i=0; i < prev_arr.size(); i+=2)
    {
       // qDebug() << "rebro " << prev_arr[i] << "-" << arr[i+1];
        g[prev_arr[i]].push_back(arr[i+1]);
        g[arr[i+1]].push_back(prev_arr[i]);

    }


}

void Deltawave1302::processGraph()
{
    std::vector<int> path;
//    for(int i=0; i < g.size(); i++)
//    {
//        std::vector<int> path;
//        dfs(i,n,m,path);
//    }
    dfs(n, n, m,path);

}

void Deltawave1302::dfs(int v, int n, int m, std::vector<int> path)
{
    color[v] = BLACK;
    path.push_back(v);
    for(int i=0; i < g[v].size(); i++)
    {
        if( g[v][i] == m ) //found a destination
        {
            //for(int j=0; j < path.size(); j++)
            //    if( path[j] == n )
            paths.push_back(path);
            //return;
        }
        if( color[g[v][i]] == WHITE)
          dfs(g[v][i],n, m, path);
    }

}


void Deltawave1302::create_Graph()
{
    int count=3;
    int i0=2;
    int n_levels=10;
    std::vector<int> prev_arr;
    g.resize(1000);
    color.resize(1000, 0);
    while( n_levels!=0 )
    {
        std::vector<int> arr;
        for(int j=i0; j<i0+count; j++)
        {
            arr.push_back( j );
        }
        i0 +=count ;
        count = count + 2;

        out_arr(arr);
        add_edges( prev_arr, arr);
        prev_arr = arr;
        n_levels--;
    }
}

Deltawave1302::Deltawave1302(int n, int m)
    : m(m), n(n)
{
    qDebug() << " m=" << m << " n=" << n;
    create_Graph();
    processGraph();
    std::sort(paths.begin(), paths.end(),
        [&](const std::vector<int>  a, std::vector<int>  b) -> bool
    {
              return a.size() < b.size();
    });
    qDebug() << "otvet " << paths[0].size();
    qDebug() << "done!";

}
