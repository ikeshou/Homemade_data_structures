#include <stdio.h>
#include "struct_for_set.h"
#include "set.h"
#include "hash_func.h"
#include "doubly.h"


int main(void) {
    chained_hashtab_t h_t = make_set();
    print_set(h_t);    // set: {}
    
    // insert
    set_insert(h_t, 1.0);
    set_insert(h_t, 2.0);
    set_insert(h_t, 7.7);    
    print_set(h_t);
    // collision (hash-number = 777)
    set_insert(h_t, 519.0);
    print_set(h_t);
    printf("\n");

    // search
    printf("search for 1.0: %s\n", set_search(h_t, 1.0)?"true":"false");    // true
    printf("search for 10000000000: %s\n", set_search(h_t, 10000000000)?"true":"false");    // false
    printf("\n");
    
    // delete
    printf("delete!\n");
    set_delete(h_t, 10000000000);    // nothing happens
    set_delete(h_t, 519.0);
    print_set(h_t);
    set_delete(h_t, 2.0);
    print_set(h_t);
    set_delete(h_t, 1.0);
    print_set(h_t);
    set_delete(h_t, 7.7);
    print_set(h_t);
    
    return 0;
}