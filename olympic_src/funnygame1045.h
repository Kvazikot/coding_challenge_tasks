#ifndef FUNNYGAME1045_H
#define FUNNYGAME1045_H

#include <QString>
#include <vector>
class FunnyGame1045
{
    enum {GRAY,WHITE,BLACK};
    bool                           win_player;
    std::vector<char>              color;
    std::vector<std::vector<int> > g;
    char dfs(int v, int e, bool found, char player);


public:
    FunnyGame1045(QString input);
};

#endif // FUNNYGAME1045_H
