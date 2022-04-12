#ifndef BINARYAPPLETREE1018_H
#define BINARYAPPLETREE1018_H

#include <vector>
#include <QString>

class TreeNode;

struct TreeVisitor
{
    int Nprune;
    int ComputeSum(TreeNode* root);
    void ResetSum(TreeNode* node);
    void Prune(TreeNode* node);
};


struct TreeNode
{
    int N;
    int w[2];
    bool prune[2];
    int sum;
    TreeNode(){ Clear(); }
    void Clear()
    {
        left = 0; right = 0;
        sum = 0; w[0] = 0; w[1] = 0;
        prune[0] = 0; prune[1] = 0;
    }
    TreeNode(int n):N(n){ Clear(); }
    TreeNode* left;
    TreeNode* right;
    bool isLeaf(){ return (left == right) || (prune[0] && prune[1]); }
    void AddBranch(TreeNode* child, int _w)
    {
        if(left==0)
        {
          left = child;
          w[0] = _w;
          return;
        }
        if(right==0)
        {
            right = child;
            w[1] = _w;
        }
    }


};

class BinaryAppleTree1018
{
public:
    std::vector<TreeNode*> tree;
    BinaryAppleTree1018(QString input);

};

#endif // BINARYAPPLETREE1018_H
