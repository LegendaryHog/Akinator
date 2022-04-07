#include "problem.h"

size_t gdcount = 0;

void AkiPrintTree (const Node* const node, FILE* f)
{
    fprintf (f, "\tNODE_%p[label = \" %s\"];\n", node, node->data);
    if (node->left)
    {
        AkiPrintTree (node->left, f);
        fprintf (f, "\tNODE_%p -> NODE_%p [label = \"Yes\", fontcolor = blue,  style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->left);
    }
    if (node->right)
    {
        AkiPrintTree (node->right, f);
        fprintf (f, "\tNODE_%p -> NODE_%p [label = \"No\", fontcolor = red, style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->right);
    }
}

int AkiGraphDump (const Node* const tree)
{
    assert (tree != NULL);
    FILE* graph = fopen ("logs/aki_dump.dot", "w");
    if (graph == NULL)
    {
        system ("mkdir logs/");
        graph = fopen ("logs/aki_dump.dot", "w");
    }
    fprintf (graph, "digraph G{\n");
    fprintf (graph, "\trankdir=TB;\n");
    fprintf (graph, "\tnode[color = forestgreen,shape=record, penwidth=3.0, style = filled, fillcolor = green];\n");
    AkiPrintTree (tree, graph);
    fprintf (graph, "}\n");
    fclose (graph);
    char* cmd_mes = (char*) calloc (LEN0, sizeof (char));
    sprintf (cmd_mes, "dot -Tpng logs/aki_dump.dot -o logs/Aki_Dump%zd.png", gdcount);
    sprintf (cmd_mes, "dot -Tpng logs/aki_dump.dot -o AkiTree/Aki_Dump%zd.png", gdcount);
    system (cmd_mes);
    free (cmd_mes);
    system ("rm logs/aki_dump.dot");
    gdcount++;
    return NO_ERR;
}

void ClearBuffer (void)
{
    while (getchar() != '\n') {;}
}
int Play (Node* const tree)
{
    if (tree == NULL)
    {
        return ERR;
    }
    Node* node = tree;
    for (;;)
    {
        if (node->left == NULL)
        {
            printf ("It is %s?\n[y/n]:", node->data);
            char input = getchar ();
            ClearBuffer ();
            if (input == 'y')
            {
                printf ("Yare-yare daze, AM I RIGHT? YES, I AM!\n");
                return NO_ERR;
            }
            else if (input == 'n')
            {
                printf ("Sorry, my bad, tell me who you mean?\n");
                char* newstr = NULL;
                size_t mem = 0;
                getline (&newstr, &mem, stdin);
                newstr[strlen(newstr) - 1] = '\0';
                printf ("How does %s differ from %s?\n", newstr, node->data);
                char* ques = NULL;
                size_t qmem = 0;
                getline (&ques, &qmem, stdin);
                size_t len = strlen (ques);
                ques[len - 1] == '\0';
                ques = (char*) realloc (ques, len + 1);
                ques[len - 1] = '?';
                ques[len] = '\0';
                SetLBranch (node, newstr);
                SetRBranch (node, node->data);
                node->data = ques;
                printf ("Ok, B'arbi, now i now this guy\n");
                return NO_ERR;
            }
        }
        //system ("espeak-ng --stdout\n");
        printf ("%s\n[y/n]:", node->data);
        char input = getchar ();
        ClearBuffer ();
        if (input == 'y')
        {
            node = node->left;
        }
        else if (input == 'n')
        {
            node = node->right;
        }
        else
        {
            system ("espeak-ng --stdout\n");
            printf ("Incorerrect input\nTry again\n");
        }
    }
    return NO_ERR;
}
void RecPrintTree (FILE* f, Node* node, size_t n)
{
    if (node == NULL)
    {
        return;
    }
    fputc ('\n', f);
    for (size_t i = 0; i < n; i++)
    {
        fputc ('\t', f);
    }
    fprintf (f, "{ %s ", node->data);
    if (node->left == NULL && node->right != NULL)
    {
        fputc ('\n', f);
        for (size_t i = 0; i < n + 1; i++)
        {
            fputc ('\t', f);
        }
        fprintf (f, "{}\n");
        RecPrintTree (f, node->right, n+1);
    }
    else if (node->left != NULL && node->right == NULL)
    {
        RecPrintTree (f, node->left, n+1);
        fputc ('\n', f);
        for (size_t i = 0; i < n + 1; i++)
        {
            fputc ('\t', f);
        }
        fprintf (f, "{}\n");
    }
    else if (node->left != NULL && node->right != NULL)
    {
        RecPrintTree (f, node->left, n+1);
        RecPrintTree (f, node->right, n+1);
    }
    else
    {
        fputc ('}', f);
        return;
    }
    fputc ('\n', f);
    for (size_t i = 0; i < n; i++)
    {
        fputc ('\t', f);
    }
    fputc ('}', f);
    return;   
}

int AkiTextDump (const char* filename, Node* tree)
{
    if (tree == NULL)
    {
        return ERR;
    }
    FILE* f = fopen (filename, "w");
    RecPrintTree (f, tree, 0);
    fclose (f);
    return NO_ERR;
}