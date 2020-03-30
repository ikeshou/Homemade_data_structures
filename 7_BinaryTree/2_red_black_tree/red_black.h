#pragma once
#include <stdbool.h>
#include "tree_struct.h"


tree_t make_empty_tree(void) ;

void inorder_traverse(tree_t, node_t);

void preorder_traverse(tree_t, node_t);

void postorder_traverse(tree_t, node_t);

node_t tree_search(tree_t, node_t, double);

node_t tree_min_node(tree_t, node_t);

node_t tree_max_node(tree_t, node_t);

node_t successor(tree_t, node_t);

node_t predecessor(tree_t, node_t);

void rb_insert_fixup(tree_t, node_t);

void insert_node(tree_t, double);

void transplant(tree_t, node_t, node_t);

void rb_delete_fixup(tree_t, node_t);

void delete_node(tree_t, node_t);

tree_t build_red_black_tree(double[], long);

