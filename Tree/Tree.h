#ifndef TREEH
#define TREEh

#include <stdio.h>
#include <stdlib.h>
#include <../common.h>

enum ERRORS {
    ERR,
    NO_ERR,
};

typedef struct Tree {
    data_t       data;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* PlantTree (data_t push);

int   ChopDown (Tree* tree);

Tree* SetLBranch  (Tree* tree, data_t push);

Tree* SetRBranch (Tree* tree, data_t push);

#endif