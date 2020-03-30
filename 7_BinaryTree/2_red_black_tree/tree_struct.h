#pragma once
#include <stdbool.h>


struct vertex {
    double value;
    bool color;    // RED or BLACK
    struct vertex* parent;    //  根の場合 NIL
    struct vertex* left;    // 葉の場合 NIL
    struct vertex* right;    // 葉の場合 NIL
};

typedef struct vertex node, *node_t;


typedef struct {
    node* root;    // 空の場合番兵の NIL を指す
    node* NIL;    // 番兵。color は BLACK だが、そのほかの属性については意味を持たない。(手続き上、属性値がセットされることはある)
} tree, *tree_t;
