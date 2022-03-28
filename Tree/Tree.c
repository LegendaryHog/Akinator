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

int SetLBranch (Tree* leaf, data_t push)
{
    if (leaf == NULL)
    {
        return ERR;
    }
    if (leaf->left != NULL)
    {
        return ERR;
    }
    leaf->left = (Tree*) calloc (1, sizeof (Tree));
    return NO_ERR;
}

int SetRBranch (Tree* leaf, data_t push)
{
    if (leaf == NULL)
    {
        return ERR;
    }
    if (leaf->right != NULL)
    {
        return ERR;
    }
    leaf->right = (Tree*) calloc (1, sizeof (Tree));
    return NO_ERR;
}