#include "problem.h"
#include "../AkiTree/AkiTree.h"

int main (void)
{
    Node* tree = PlantTree (NULL);
    Pull ();
    if (ScanAllTree ("AkiTree/AkiTree.txt", tree) == ERR)
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
    AkiTextDump  ("AkiTree/AkiTree.txt", tree);
    Push ();
    ChopDown (tree);
    return 0;
}