#include "Tree.h"

int main (void)
{
    Node* tree = PlantTree (10);
    SetLBranch (tree, 20);
    SetRBranch (tree, 30);
    SetLBranch (tree->left, 40);
    SetRBranch (tree->left, 50);
    TreeDbgDump (tree);
    ChopDown (tree);
    return 0;
}