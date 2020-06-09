#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree_struct.h"
#include "rotate.h"
#include "red_black.h"


int main(void) {
    tree_t t_t = make_empty_tree();
    printf("tree: ");
    inorder_traverse(t_t, t_t->root);    // tree: 
    printf("\n");
    printf("\n");

    /* insert */
    printf("let's insert!\n");

    insert_node(t_t, 1.0);
    /*
                    1(b)
    */
    preorder_traverse(t_t, t_t->root);    // 1.000(B) 
    printf("\n");
    insert_node(t_t, 2.0);
    /*
                    1(b)
                                2(r)
    */
    preorder_traverse(t_t, t_t->root);    // 1.000(B) 2.000(R) 
    printf("\n");    
    insert_node(t_t, 3.0);
    /*
                    2(b)
        1(b)                     3(b)
    */
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 3.000(B) 
    printf("\n");        
    insert_node(t_t, 2.0);
    /*
                    2(b)
        1(b)                     3(b)
                            2(r)
    */    
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 3.000(B) 2.000(R) 
    printf("\n");        
    insert_node(t_t, 1.0);
    /*
                    2(b)
        1(b)                     3(b)
             1(r)            2(r)
    */
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 
    printf("\n");        
    insert_node(t_t, 4.0);
    /*
                    2(b)
        1(b)                     3(b)
             1(r)            2(r)     4(r)
    */    
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 4.000(R)
    printf("\n");        
    insert_node(t_t, 7.0);
    /*
                    2(b)
        1(b)                     4(r)
             1(r)            3(b)     7(b)
                           2(r)
    */        
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 1.000(R) 4.000(R) 3.000(B) 2.000(R) 7.000(B)
    printf("\n");        
    insert_node(t_t, 6.0);
    /*
                    2(b)
        1(b)                     4(r)
             1(r)            3(b)     7(b)
                           2(r)      6(r)
    */
    preorder_traverse(t_t, t_t->root);    // 2.000(B) 1.000(B) 1.000(R) 4.000(R) 3.000(B) 2.000(R) 7.000(B) 6.000(R)
    printf("\n");           
    insert_node(t_t, 5.0);
    /*
                    4(b)
        2(b)                     6(b)
    1(b)      3(b)           5(b)     7(b)
      1(r)   2(r)
    */    
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 6.000(B) 5.000(B) 7.000(B)
    printf("\n");            
    insert_node(t_t, 5.0);
    /*
                    4(b)
        2(b)                     6(b)
    1(b)      3(b)           5(b)     7(b)
      1(r)   2(r)              5(r)
    */        
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 6.000(B) 5.000(B) 5.000(R) 7.000(B) 
    printf("\n");        
    insert_node(t_t, 8.0);
    /*
                    4(b)
        2(b)                     6(b)
    1(b)      3(b)           5(b)     7(b)
      1(r)   2(r)              5(r)     8(r)
    */
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 6.000(B) 5.000(B) 5.000(R) 7.000(B) 8.000(R)
    printf("\n");      
    insert_node(t_t, 9.0);
    /*
                    4(b)
        2(b)                     6(b)
    1(b)      3(b)           5(b)     8(r)
      1(r)   2(r)              5(r)  7(b)9(b)                                          
    */
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 6.000(B) 5.000(B) 5.000(R) 8.000(R) 7.000(B) 9.000(B) 
    printf("\n");        
    insert_node(t_t, 0.0);
    /*
                     4(b)
         2(b)                     6(b)
     1(b)      3(b)           5(b)     8(r)
    0(r)1(r)  2(r)              5(r)  7(b)9(b)                                          
    */
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 0.000(R) 1.000(R) 3.000(B) 2.000(R) 6.000(B) 5.000(B) 5.000(R) 8.000(R) 7.000(B) 9.000(B) 
    printf("\n");
    printf("\n");

    /* search, tree_min, tree_max, successor, predecessor */
    printf("search for 6.0: found at %p\n", tree_search(t_t, t_t->root, 6.0));    // search for 6.0: found at 0x7fc796405a70
    printf("tree_min: %.3f\n", tree_min_node(t_t, t_t->root)->value);    // tree_min: 0.000
    printf("tree_max: %.3f\n", tree_max_node(t_t, t_t->root)->value);    // tree_max: 9.000
    printf("next to 6.0: %.3f\n", successor(t_t, tree_search(t_t, t_t->root, 6.0))->value);    // next to 6.0: 7.000
    printf("previous to 6.0: %.3f\n", predecessor(t_t, tree_search(t_t, t_t->root, 6.0))->value);    // previous to 6.0: 5.000
    printf("\n");


    /* delete */
    printf("let's delete!\n");
    delete_node(t_t, tree_search(t_t, t_t->root, 6.0));
    /*
    ただの削除だと
                     4(b)
         2(b)                     7(b)
     1(b)      3(b)           5(b)     8(r)
    0(r)1(r)  2(r)              5(r)   y 9(b)
    となる。これを rb_delete_fix すると (case 4-1)
                     4(b)
         2(b)                     7(b)
     1(b)      3(b)           5(b)     8(b)
    0(r)1(r)  2(r)              5(r)     9(r)
    となるはず。    
    */    
    preorder_traverse(t_t, t_t->root);    // 4.000(B) 2.000(B) 1.000(B) 0.000(R) 1.000(R) 3.000(B) 2.000(R) 7.000(B) 5.000(B) 5.000(R) 8.000(B) 9.000(R) 
    printf("\n");

    delete_node(t_t, tree_search(t_t, t_t->root, 4.0));
    /*
    ただの削除だと
                     5(b)
         2(b)                     7(b)
     1(b)      3(b)            y5(r)   8(b)
    0(r)1(r)  2(r)                       9(r)
    となるはず。これを rb_delete_fix すると (case 3-1)
                     5(b)
         2(b)                     8(b)
     1(b)      3(b)            7(b)   9(b)
    0(r)1(r)  2(r)            5(r)          
    となるはず。      
    */            
    preorder_traverse(t_t, t_t->root);    // 5.000(B) 2.000(B) 1.000(B) 0.000(R) 1.000(R) 3.000(B) 2.000(R) 8.000(B) 7.000(B) 5.000(R) 9.000(B) 
    printf("\n");

    delete_node(t_t, tree_search(t_t, t_t->root, 0.0));
    /*
    ただの削除でおしまい
                     5(b)
         2(b)                     8(b)
     1(b)      3(b)            7(b)   9(b)
       1(r)  2(r)            5(r)         
    となるはず。
    */          
    preorder_traverse(t_t, t_t->root);    // 5.000(B) 2.000(B) 1.000(B) 1.000(R) 3.000(B) 2.000(R) 8.000(B) 7.000(B) 5.000(R) 9.000(B)
    printf("\n");

    delete_node(t_t, tree_search(t_t, t_t->root, 1.0));
    /*
    ただの削除だと
                     5(b)
         2(b)                     8(b)
     y1(r)    3(b)            7(b)   9(b)
             2(r)            5(r)      
    となるはず。これを rb_delete_fix すると (case 2-1)
                     5(b)
         2(b)                     8(b)
      2(b)    3(b)            7(b)   9(b)
     1(r)                    5(r)       
    となるはず。
    */
    preorder_traverse(t_t, t_t->root);   // 5.000(B) 2.000(B) 2.000(B) 1.000(R) 3.000(B) 8.000(B) 7.000(B) 5.000(R) 9.000(B) 
    printf("\n");

    delete_node(t_t, tree_search(t_t, t_t->root, 2.0));
    /*
    ただの削除だと
                     5(b)
         3(b)                    8(b)
      2(b)    y               7(b)   9(b)
     1(r)                    5(r)            
    となるはず。これを rb_delete_fix すると (case 3-2)
                     5(b)
         2(b)                    8(b)
      1(b)   3(b)             7(b)   9(b)
                            5(r)           
    */
    preorder_traverse(t_t, t_t->root);   // 5.000(B) 2.000(B) 1.000(B) 3.000(B) 8.000(B) 7.000(B) 5.000(R) 9.000(B)
    printf("\n");

    delete_node(t_t, tree_search(t_t, t_t->root, 5.0));
    /*
    ただの削除でおしまい
                     5(b)
         2(b)                    8(b)
      1(b)   3(b)             7(b)   9(b)                   
    */
    printf("\n");
    
    preorder_traverse(t_t, t_t->root);   // 5.000(B) 2.000(B) 1.000(B) 3.000(B) 8.000(B) 7.000(B) 9.000(B) 
    printf("\n");
    postorder_traverse(t_t, t_t->root);    // 1.000(B) 3.000(B) 2.000(B) 7.000(B) 9.000(B) 8.000(B) 5.000(B) 
    printf("\n");
    inorder_traverse(t_t, t_t->root);    // 1.000(B) 2.000(B) 3.000(B) 5.000(B) 7.000(B) 8.000(B) 9.000(
    printf("\n");

    return 0;
}