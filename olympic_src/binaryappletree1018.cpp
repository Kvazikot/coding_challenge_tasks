#include <QDebug>
#include <QStringList>
#include "binaryappletree1018.h"

int TreeVisitor::ComputeSum(TreeNode* root)
{
    qDebug() << root->N << " " << root->sum << " ";

    if(root->left && !root->prune[0])
    {
        root->sum+=root->w[0] + ComputeSum(root->left);
    }
    if(root->right && !root->prune[1])
    {
        root->sum+=root->w[1] + ComputeSum(root->right);
    }


    return root->sum;
}

void TreeVisitor::ResetSum(TreeNode* node)
{
    if(node->left)
        ResetSum(node->left);
    if(node->right)
        ResetSum(node->right);
    node->sum = 0;

}

void TreeVisitor::Prune(TreeNode* node)
{
    if( node->left && node->right  )
    {
        if( (node->left->sum + node->w[0]) >= (node->right->sum  + node->w[1]) )
        {
            if( node->right->isLeaf() )
            {
                node->prune[1] = 1; // prune right
                Nprune--;
                if(Nprune == 0) return;
            }
            Prune(node->left);

        }
        else
        {
            if( node->left->isLeaf() )
            {
                node->prune[0] = 1; // prune left
                Nprune--;
                if(Nprune == 0) return;
            }
            Prune(node->right);

        }

    }
}



BinaryAppleTree1018::BinaryAppleTree1018(QString input)
{
    QStringList lines = input.split(",");
    QStringList parts = lines[0].split(" ");
    int N = parts[0].toInt();
    int Q = parts[1].toInt();
    //create tree nodes
    for(int i=0; i <= N; i++)
    {
        //tree.push_back(std::vector<TreeNode>());
        tree.push_back(new TreeNode(i));
    }

    //create branches
    int Nbranches = 0;
    for(int i=1; i < lines.size(); i++)
    {
        parts = lines[i].split(" ");
        int n1 = parts[0].toInt();
        int n2 = parts[1].toInt();
        int w = parts[2].toInt();
        tree[n1]->AddBranch(tree[n2], w);
        Nbranches++;
        //tree[n1].push_back()
    }

    TreeVisitor visitor;
    visitor.Nprune = Nbranches - Q;
    tree[1]->sum = visitor.ComputeSum(tree[1]);
    qDebug() << "starting sum = " << tree[1]->sum;
    while(visitor.Nprune!=0)
    {
        visitor.Prune(tree[1]);
        visitor.ResetSum(tree[1]);
        qDebug() << "Prune " << visitor.Nprune << " sum = " << visitor.ComputeSum(tree[1]);

    }

    qDebug() << "binary tree!";
}
