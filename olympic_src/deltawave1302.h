#ifndef DELTAWAVE1302_H
#define DELTAWAVE1302_H

#include <vector>

class Deltawave1302
{
public:
    Deltawave1302(int n, int m);
    void add_edges( std::vector<int> prev_arr, std::vector<int> arr);
    void dfs(int v,  int n, int m, std::vector<int> path);
    void processGraph();
    int m;
    int n;
    enum {WHITE=0,GRAY,BLACK};
    std::vector<char>   color;
    std::vector< std::vector<int> > g;
    std::vector< std::vector<int> > paths;
    void create_Graph();
};

#endif // DELTAWAVE1302_H
