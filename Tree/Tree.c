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

void PrintTree (const Node* const node, FILE* f)
{
    fprintf (f, "\tNODE_%p[label = \"{ <_node_> node:\\n%p | data: %d | { <left> left:\\n%p | <right> right:\\n%p} }\"];\n", node, node, node->data, node->left, node->right);
    if (node->left)
    {
        PrintTree (node->left, f);
        fprintf (f, "\tNODE_%p:left:s -> NODE_%p:_node_:n [style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->left);
    }
    if (node->right)
    {
        PrintTree (node->right, f);
        fprintf (f, "\tNODE_%p:right:s -> NODE_%p:_node_:n [style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->right);
    }
}

int TreeDbgDump (const Node* const tree)
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
    fprintf (graph, "\tnode[color = forestgreen,shape=record, penwidth=3.0, style = filled, fillcolor = green];\n");
    PrintTree (tree, graph);
    fprintf (graph, "}\n");
    fclose (graph);
    char* cmd_mes = (char*) calloc (LEN0, sizeof (char));
    sprintf (cmd_mes, "dot -Tpng logs/graph_dump.dot -o logs/Graph_Dump%zd.png", gdcounter);
    system (cmd_mes);
    free (cmd_mes);
    system ("rm logs/graph_dump.dot");
    gdcounter++;
    return NO_ERR;
}

int ScanAllTree (const char* filename, Node* tree)
{
    if (tree == NULL)
    {
        return ERR;
    }
    if (filename == NULL)
    {
        return ERR;
    }
    long bufsz = 0;
    char* buffer = Read (filename, &bufsz);
    
    if (RecScanTree (buffer, tree) == 0)
    {
        return ERR;
    }
    else
    {
        return NO_ERR;
    }
}

size_t RecScanTree (const char* text, Node* node)
{
    size_t i = 0;
    i += SkipEnters (text + i);
    if (text[i] != '{')
    {
        printf ("Not meet {, symbol = %c (%d)\n", text[i], text[i]);
        return 0;
    }
    else
    {
        i++;
    }
    i += SkipSpaces (text + i);
    i += ScanArg (text + i, node);
    i += SkipSpaces (text + i);
    if (text[i] == '}')
    {
        i++;
        return i;
    }
    i += SkipEnters (text + i);
    if (CheckEmpty (text + i) == 0)
    {
        SetLBranch (node, 0);
        size_t dil = RecScanTree (text + i, node->left);
        if (dil == 0)
        {
            return 0;
        }
        else
        {
            i += dil;
        }
    }
    else
    {
        i += 2;
    }
    i += SkipEnters (text + i);
    if (CheckEmpty (text + i) == 0)
    {
        SetRBranch (node, 0);
        size_t dir = RecScanTree (text + i, node->right);
        if (dir == 0)
        {
            return 0;
        }
        else
        {
            i += dir;
        }
    }
    else
    {
        i += 2;
    }
    i += SkipEnters (text + i);
    if (text[i] != '}')
    {
        return 0;
    }
    else
    {
        i++;
        return i;
    }
}

char* Read (const char* filename, long* ptrbufsz)
{
    FILE* text = fopen (filename, "r");
    fseek (text, 0, SEEK_SET);
    long start = ftell (text);
    fseek (text, 0, SEEK_END);
    long end = ftell (text);
    fseek (text, 0, SEEK_SET);
    *ptrbufsz = end - start;

    char* buffer = (char*) calloc (*ptrbufsz + 1, sizeof (char));
    fread (buffer, sizeof (char), *ptrbufsz, text);
    fclose (text);
    return buffer;
}

size_t SkipSpaces (const char* text)
{
    size_t i = 0;
    for (i = 0; text[i] == ' ' || text[i] == '\t'; i++) {;}
    return i;
}

size_t SkipEnters (const char* text)
{
    size_t i = 0;
    for (i = 0; text[i] == ' ' || text[i] == '\t' || text[i] == '\n'; i++) {;}
    return i;
}

size_t ScanArg (const char* text, Node* node)
{
    char* arg = (char*) calloc (10, sizeof (char));
    sscanf (text, "%[0-9]", arg);
    size_t len = strlen(arg);
    sscanf (arg, "%d", &node->data);
    free (arg);
    return len;
}

int CheckEmpty (const char* text)
{
    size_t i = 0;
    for (i = 0; text[i] != '}'; i++) {;}
    if (i == 1)
    {
        return 1;
    }
    return 0;
}