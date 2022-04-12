//http://acm.timus.ru/problem.aspx?space=1&num=1003
#include <algorithm>
#include <QStringList>
#include <QDebug>
#include "parity1003.h"

Parity1003::Parity1003(QString input)
{
    QStringList list = input.split(",");
    n_bits = list[0].toInt();
    n_rules = list[1].toInt();

    //Create graph
    for(int i = 0; i < n_rules; i++)
    {
        QStringList list2 = list[i+2].split(" ");
        int id1 = list2[0].toInt();
        int id2 = list2[1].toInt();

        bool even;
        if( list2[2] == "even" )
            even = true;
        else
            even = false;

        Treenode* node1 = findNode(id1);
        if( node1 == 0 )
        {
            node1 = new Treenode(id1);
            nodes.push_back(node1);
        }

        Treenode* node2 = findNode(id2);
        if( node2 == 0 )
        {
            node2 = new Treenode(id2);
            nodes.push_back(node2);
        }

        if( findConnection(id1, id2) == 0 )
        {
            Connection* newConnection = new Connection(id1, id2, even);
            connections.push_back(newConnection);
            node1->connections.push_back(newConnection);
            node2->connections.push_back(newConnection);
        }

    }
    mainLoop();
}

void Parity1003::ResetValues()
{
    for(auto it=nodes.begin(); it!=nodes.end(); it++)
    {
            Treenode* node = *(it);
            node->val = -1;
    }

}

bool Parity1003::checkConnections()
{
    for(auto it2=connections.begin(); it2!=connections.end(); it2++)
    {
        Connection* con = *(it2);
        Treenode* node1 = findNode(con->id1);
        Treenode* node2 = findNode(con->id2);
        if( con->even != !(node1->val ^ node2->val) )
            return false;
    }
    return true;
}

void Parity1003::assignValues()
{
    for(auto it=nodes.begin(); it!=nodes.end(); it++)
    {
        Treenode* node = *(it);

        //assign random val
        if( node->val == -1)
        {
            if( rand()%100 > 50)
                node->val = 1;
            else
                node->val = 0;
        }
        //seek thro connections
        for(auto it2=node->connections.begin(); it2!=node->connections.end(); it2++)
        {
            Connection* con = *(it2);
            int id2 = con->getSecondNodeID(node);
            Treenode* node2 = findNode(id2);
            if( node2->val == -1)
            {
                if( con->even )
                    node2->val = node->val;
                else
                    node2->val = !node->val;
            }

        }

    }
}

void Parity1003::mainLoop()
{

    int numIterations = 0;
    while( numIterations < 1000)
    {
        std::sort(nodes.begin(), nodes.end(),
            [](const Treenode*  a, const Treenode*  b) -> bool
        {
             return a->connections.size() > b->connections.size();
        });

        ResetValues();
        assignValues();
        if( checkConnections() )
        {
            std::sort(nodes.begin(), nodes.end(),
                [](const Treenode*  a, const Treenode*  b) -> bool
            {
                 return a->id < b->id;
            });

            QString out;
            QDebug dbg(&out);
            for(auto it=nodes.begin(); it!=nodes.end(); it++)
            {
                Treenode* node = *(it);
                dbg << "," << node->val;
            }

            if( !checkMirrorSeq(out))
            if( sequences.find(out) == sequences.end())
            {
                sequences[out] = 1;
                qDebug() << out;
            }
        }

        numIterations++;
    }
    qDebug() << "numIterations=" << numIterations;
    qDebug() << "num unique sequences=" << sequences.size();



}

bool  Parity1003::checkMirrorSeq(QString seq)
{
    for(int i=0; i < seq.size(); i++)
    {
        if( seq[i] == '1' )
        {
            seq[i] = '0';
            continue;
        }
        if( seq[i] == '0' )
            seq[i] = '1';
    }
    return sequences.find(seq) != sequences.end();
}

Treenode* Parity1003::findNode(int id)
{
    std::vector<Treenode*>::iterator it;
    for(it=nodes.begin(); it!=nodes.end(); it++)
        if( (*it)->id == id )
            return *it;
    return 0;
}

Connection* Parity1003::findConnection(int id1, int id2)
{
    std::vector<Connection*>::iterator it;
    for(it=connections.begin(); it!=connections.end(); it++)
    {
        if (( ((*it)->id1 == id1) && ((*it)->id2 == id2) ) ||
           ( ((*it)->id2 == id1) && ((*it)->id2 == id1) ) )
        {
            return *it;
        }
    }
    return 0;
}
