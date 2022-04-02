#ifndef PROBLEMH
#define PROBLEMH

#include "../Tree/Tree.h"
#include "../common.h"

int AkiGraphDump (const Node* const tree);

int Play         (Node* const tree);

int AkiTextDump  (const char* filename, Node* tree);

void ClearBuffer (void);

#endif