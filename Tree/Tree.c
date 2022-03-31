#include "Tree.h"

size_t gdcounter = 0;

Node* PlantTree (data_t push)
{
    Node* tree = (Node*) calloc (1, sizeof (Node));
    tree->data = push;
    return tree;
}

int ChopDown (Node* tree)
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

int SetLBranch (Node* leaf, data_t push)
{
    if (leaf == NULL)
    {
        return ERR;
    }
    if (leaf->left != NULL)
    {
        return ERR;
    }
    leaf->left = (Node*) calloc (1, sizeof (Node));
    leaf->left->data = push;
    return NO_ERR;
}

int SetRBranch (Node* leaf, data_t push)
{
    if (leaf == NULL)
    {
        return ERR;
    }
    if (leaf->right != NULL)
    {
        return ERR;
    }
    leaf->right = (Node*) calloc (1, sizeof (Node));
    leaf->right->data = push;
    return NO_ERR;
}

void PrintTree (Node* node, FILE* f)
{
    fprintf (f, "\tNODE_%p[label = \"{ <_node_> node:\\n%p | data: %d | { <left> left:\\n%p | <right> right:\\n%p} }\"];\n", node, node, node->data, node->left, node->right);
    if (node->left)
    {
        PrintTree (node->left, f);
        fprintf (f, "\tNODE_%p:left:s -> NODE_%p:_node_:n [dir = both, arrowtail = dot, color = red];\n", node, node->left);
    }
    if (node->right)
    {
        PrintTree (node->right, f);
        fprintf (f, "\tNODE_%p:right:s -> NODE_%p:_node_:n [dir = both, arrowtail = dot, color = red];\n", node, node->right);
    }
}

int TreeDbgDump (Node* tree)
{
    assert (tree != NULL);
    FILE* graph = fopen ("logs/graph_dump.dot", "w");
    if (graph == NULL)
    {
        system ("mkdir logs/");
        graph = fopen ("logs/graph_dump.dot", "w");
    }
    fprintf (graph, "digraph G{\n");
    fprintf (graph, "\trankdir=TB;\n");
    fprintf (graph, "\tnode[color=\"red\",shape=record, penwidth=2.0, style = filled, fillcolor = aqua];\n");
    PrintTree (tree, graph);
    fprintf (graph, "}\n");
    fclose (graph);
    char* cmd_mes = (char*) calloc (LEN0, sizeof (char));
    sprintf (cmd_mes, "dot -Tpng logs/graph_dump.dot -o logs/Graph_Dump%zd.png", gdcounter);
    system (cmd_mes);
    free (cmd_mes);
    //system ("rm logs/graph_dump.dot");
    gdcounter++;
    return NO_ERR;
}
