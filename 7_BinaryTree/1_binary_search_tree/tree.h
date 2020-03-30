#pragma once


struct vertex {
    double value;
    struct vertex* parent;    // 値の場合 NULL
    struct vertex* left;    // 葉の場合 NULL
    struct vertex* right;    // 葉の場合 NULL
};

typedef struct vertex node, *node_t;

typedef struct {
    node* root;    // 空の場合 NULL
} tree, *tree_t;


tree_t make_empty_tree(void);

void inorder_traverse(node_t);

void preorder_traverse(node_t);

void postorder_traverse(node_t);

node_t tree_search(node_t, double);

node_t tree_min_node(node_t);

node_t tree_max_node(node_t);

node_t successor(node_t);

node_t predecessor(node_t);

void insert_node(tree_t, double);

void transplant(tree_t, node_t, node_t);

void delete_node(tree_t, node_t);

tree_t build_BST(double[], long);

void swap(double*, double*);

void shuffle(double[], long);

tree_t build_Randomized_BST(double[], long);
