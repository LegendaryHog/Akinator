#include "Tree.h"

int main (void)
{
    Node* tree = PlantTree (NULL);
    /*SetLBranch (tree, 20);
    SetRBranch (tree, 30);
    SetLBranch (tree->left, 40);
    SetRBranch (tree->left, 50);
    SetLBranch (tree->right, 60);*/
    ScanAllTree ("Tree/test.txt", tree);
    TreeDbgDump (tree);
    ChopDown (tree);
    return 0;
}