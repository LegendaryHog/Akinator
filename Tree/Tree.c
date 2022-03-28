#include <Tree.h>

Tree* PlantTree (data_t push)
{
    return (Tree*) calloc (1, sizeof (Tree));
}

int ChopDown (Tree* tree)
{
    if (tree == NULL)
    {
        return ERR;
    }
    if (tree->left != NULL)
    {
        ChopDown (tree->left);
    }
    if (tree->right != NULL)
    {
        ChopDown (tree->right);
    }
    free (tree);
    return NO_ERR;
}

Tree* SetLBranch (Tree* tree, data_t push)
{
    
}