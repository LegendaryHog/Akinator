#ifndef TREEH
#define TREEh

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

Node* PlantTree   (data_t push);

int   ChopDown    (Node* tree);

int   SetLBranch  (Node* tree, data_t push);

int   SetRBranch  (Node* tree, data_t push);

int   TreeDbgDump (Node* tree);

int   TreeDump    (Node* tree);

#endif