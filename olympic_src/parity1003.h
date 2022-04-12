#ifndef PARITY1003_H
#define PARITY1003_H

#include <QString>
#include <vector>
#include <map>

class Connection;

class Treenode
{
public:
    int id;
    int val;
    std::vector<Connection*> connections;
    Treenode(int id)
        :id(id)
    {
        val = -1;
    }

};

class Connection
{
public:
    Connection(int id1, int id2, bool even)
        :id1(id1),id2(id2),even(even)
    {}
    int getSecondNodeID(Treenode* node)
    {
        if(node->id == id1)
            return id2;
        if(node->id == id2)
            return id1;
        return 0;
    }

    int id1;
    int id2;
    bool even;
};

class Parity1003
{
public:
    int n_bits;
    int n_rules;
    std::map<QString, int> sequences;
    std::vector<Treenode*> nodes;
    std::vector<Connection*> connections;

    Parity1003(QString input);
    Treenode* findNode(int id);
    bool  checkMirrorSeq(QString seq);
    Connection* findConnection(int id1, int id2);
    void ResetValues();
    void mainLoop();
    bool checkConnections();
    void assignValues();
};

#endif // PARITY1003_H
