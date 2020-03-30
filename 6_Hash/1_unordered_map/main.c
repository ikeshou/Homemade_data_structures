#include <stdio.h>
#include "hash_table.h"
#include "hash_func.h"
#include "doublyLL_record.h"


int main(void) {
    chained_hashtab_t h_t = make_chained_hash_table();
    print_chained_hash(h_t);    // hashtable: {}
    
    // insert
    chained_hash_insert(h_t, make_record("hoge", 1.0));
    chained_hash_insert(h_t, make_record("piyo", 2.0));
    print_chained_hash(h_t);
    // update
    chained_hash_insert(h_t, make_record("hoge", 3.0));
    print_chained_hash(h_t);
    // collision (hash-number = 472)
    chained_hash_insert(h_t, make_record("::", 4.0));
    print_chained_hash(h_t);
    printf("\n");
    // search
    printf("search for 'hoge' value: %.3f\n", chained_hash_search(h_t, "hoge"));    // 3.000
    printf("search for 'piyo' value: %.3f\n", chained_hash_search(h_t, "piyo"));    // 2.000
    printf("search for '::' value: %.3f\n", chained_hash_search(h_t, "::"));    // 4.000
    printf("\n");
    // delete
    chained_hash_delete(h_t, "non-existent");    // nothing happens
    chained_hash_delete(h_t, "piyo");
    print_chained_hash(h_t);
    chained_hash_delete(h_t, "hoge");
    print_chained_hash(h_t);
    chained_hash_delete(h_t, "::");
    print_chained_hash(h_t);
    
    return 0;
}