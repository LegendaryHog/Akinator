#ifndef TREEH
#define TREEh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../common.h"

#define LEN0 90

enum ERRORS {
    ERR,
    NO_ERR,
};

typedef struct Node {
    data_t       data;
    struct Node* left;
    struct Node* right;
} Node;

Node*  PlantTree   (data_t push);

int    ChopDown    (Node* tree);

int    SetLBranch  (Node* tree, data_t push);

int    SetRBranch  (Node* tree, data_t push);

int    TreeDbgDump (const Node* const tree);

int    TreeDump    (const Node* const tree);

int    ScanAllTree (const char* filename, Node* tree);

size_t RecScanTree (const char* text, Node* node);

char*  Read        (const char* filename, long* ptrbufsz);

size_t SkipSpaces  (const char* text);

size_t SkipEnters  (const char* text);

size_t ScanArg     (const char* text, Node* node);

int    CheckEmpty  (const char* text);

#endif