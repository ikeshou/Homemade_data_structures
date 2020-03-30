#include <stdio.h>
#include "tree.h"
#include "rotate.h"


int main(void) {
    tree_t t_t = make_empty_tree();
    printf("tree: ");
    inorder_traverse(t_t->root);    // tree: 
    printf("\n");
    

    insert_node(t_t, 1.0);
    insert_node(t_t, 2.0);
    insert_node(t_t, 3.0);
    insert_node(t_t, 2.0);
    insert_node(t_t, 1.0);
    insert_node(t_t, 4.0);
    insert_node(t_t, 7.0);
    insert_node(t_t, 6.0);
    insert_node(t_t, 5.0);
    insert_node(t_t, 5.0);
    insert_node(t_t, 8.0);
    insert_node(t_t, 9.0);
    insert_node(t_t, 0.0);
    /*
                    1
    0                               2
                        1                      3
                                        2             4
                                                           7
                                                        6     8
                                                      5          9
                                                       5
    という形で挿入されているはず
    */
    inorder_traverse(t_t->root);    // 0.000 1.000 1.000 2.000 2.000 3.000 4.000 5.000 5.000 6.000 7.000 8.000 9.000
    printf("\n");
    preorder_traverse(t_t->root);    // 1.000 0.000 2.000 1.000 3.000 2.000 4.000 7.000 6.000 5.000 5.000 8.000 9.000 
    printf("\n");
    postorder_traverse(t_t->root);    // 0.000 1.000 2.000 5.000 5.000 6.000 9.000 8.000 7.000 4.000 3.000 2.000 1.000 
    printf("\n");
    printf("\n");

    /* max, min */
    printf("max: %.3f\n", tree_max_node(t_t->root)->value);    // max: 9.000
    printf("min: %.3f\n", tree_min_node(t_t->root)->value);    // min: 0.000
    printf("\n");

    /* search */
    node_t first_2 = tree_search(t_t->root, 2.0);
    printf("search for 2.0: %.3f(@%p)\n", first_2->value, first_2);    // search for 2.0: 2.000(@0x7fea46405870)
    node_t second_2 = tree_search(first_2->right, 2.0);    // 同じ値はあるとしたら最初に発見した右の部分木の中
    printf("search for 2.0: %.3f(@%p)\n", second_2->value, second_2);    // search for 2.0: 2.000(@0x7fea464058b0)
    printf("\n");

    /* insert */
    insert_node(t_t, 4.0);
    inorder_traverse(t_t->root);    // 0.000 1.000 1.000 2.000 2.000 3.000 4.000 4.000 5.000 5.000 6.000 7.000 8.000 9.000 
    printf("\n");
    
    /*
                    1
    0                               2
                        1                      3
                                        2             4
                                                           7
                                                        6     8
                                                      5          9
                                                     4 5
    となっているはず
    */    

    /* delete */
    printf("delete!\n");
    delete_node(t_t, first_2);
    /*
                    1
    0                               2
                        1                      3
                                                      4
                                                           7
                                                        6     8
                                                      5          9
                                                     4 5
    となっているはず
    */        
    delete_node(t_t, second_2);
    /*
                    1
    0                               3
                        1                       4
                                                    7
                                                  6   8
                                                 5      9
                                                4 5
    となっているはず
    */    
    delete_node(t_t, tree_search(t_t->root, 1.0));
    /*
                    1
    0                               3
                                               4
                                                    7
                                                  6   8
                                                 5      9
                                                4 5
    となっているはず
    */        
    inorder_traverse(t_t->root);    // 0.000 1.000 3.000 4.000 4.000 5.000 5.000 6.000 7.000 8.000 9.000 
    printf("\n");
    preorder_traverse(t_t->root);    // 1.000 0.000 3.000 4.000 7.000 6.000 5.000 4.000 5.000 8.000 9.000 
    printf("\n");
    postorder_traverse(t_t->root);    // 0.000 4.000 5.000 5.000 6.000 9.000 8.000 7.000 4.000 3.000 1.000 
    printf("\n");
    printf("\n");


    /* rotate */
    printf("let's rotate! (rotation will be used when implementing red-black-trees.)\n");
    left_rotate(t_t, tree_search(t_t->root, 3.0));
    /*
                    1
    0                               4
                             3               7
                                           6   8
                                         5       9
                                        4 5
    となっているはず
    */            
    preorder_traverse(t_t->root);    // 1.000 0.000 4.000 3.000 7.000 6.000 5.000 4.000 5.000 8.000 9.000
    printf("\n");
    right_rotate(t_t, tree_search(t_t->root, 6.0));
    /*
                    1
    0                               4
                             3               7
                                           5   8
                                         4  6    9
                                           5
    となっているはず
    */
   preorder_traverse(t_t->root);    // 1.000 0.000 4.000 3.000 7.000 5.000 4.000 6.000 5.000 8.000 9.000 
   printf("\n");
   printf("\n");

    

    printf("build binary search tree (BST) / randomized binary search tree (RBST) from an array of double.\n");
    double arr[7] = {8.6, 2.3, 9.9, 6.9, 10.0, 2.3, 5.5};
    tree_t built_tree_normal = build_BST(arr, sizeof(arr)/sizeof(double));
    inorder_traverse(built_tree_normal->root);    // 2.300 2.300 5.500 6.900 8.600 9.900 10.000 
    printf("\n");
    tree_t built_tree_randomized = build_Randomized_BST(arr, sizeof(arr)/sizeof(double));    // 2.300 2.300 5.500 6.900 8.600 9.900 10.000 
    inorder_traverse(built_tree_randomized->root);
    printf("\n");

    return 0;
}
