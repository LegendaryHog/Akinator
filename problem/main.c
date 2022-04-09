#include "problem.h"

void Pull (void)
{
    system ("git -C AkiTree/ pull origin master\n");
}

void Push (void)
{
    system ("git -C AkiTree/ add AkiTree.txt\n");
    system ("git -C AkiTree/ commit -m \"Fun\"\n");
    system ("git -C AkiTree/ push origin master\n");
}

int main (void)
{
    Pull ();
    Node* tree = PlantTree (NULL);
    if (ScanAllTree ("AkiTree.txt", tree) == ERR)
    {
        fprintf (stderr, "Scan ERROR\n");
    }
    for (;;)
    {
        Play (tree);
        printf ("Do you want to play again?\n[y/n]:");
        char input = getchar ();
        ClearBuffer ();
        while (input != 'y' && input != 'n')
        {
            printf ("Incorrect input, try again\n[y/n]:");
            input = getchar ();
            printf ("input = %c (%d)\n", input, input);
            ClearBuffer ();
        }
        if (input == 'n')
        {
            printf ("With best regards!\n");
            break;
        }
    }
    AkiGraphDump (tree);
    AkiTextDump  ("AkiTree.txt", tree);
    ChopDown (tree);
    Push ();
    return 0;
}