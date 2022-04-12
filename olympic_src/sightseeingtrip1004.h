#ifndef SIGHTSEEINGTRIP1004_H
#define SIGHTSEEINGTRIP1004_H

#include <QString>
#include <vector>
#include <map>

class SightseeingTrip1004
{
public:
    enum {WHITE,GRAY,BLACK};
    SightseeingTrip1004(QString input);
    void Clear();
    void dfs(int v, std::vector<int> path);

    void printPath(std::vector<int> path);
    void selectPath();
    int  pathHash(std::vector<int> path);
    void processGrapth();
    int  getPathDist(std::vector<int> path);
private:
    std::vector< std::vector<int> > g; // граф
    std::vector< std::vector<int> > paths;
    std::map<int,int>  hashes;
    std::map<std::pair<int,int>, int> dist;
    std::vector<char>   color;

};

#endif // SIGHTSEEINGTRIP1004_H
