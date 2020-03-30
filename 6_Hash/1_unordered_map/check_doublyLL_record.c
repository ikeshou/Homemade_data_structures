#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct_for_hash.h"
#include "doublyLL_record.h"


int main(void) {
    DoublyLL_t ll_t = make_empty_doubly_ll();
    char* name[] = {"hoge", "piyo", "moo", "bow"};
    srand(time(NULL));
    for (int i=0; i<sizeof(name)/sizeof(char*); i++) {
        record_t tmp = make_record(name[i], (double)rand()/RAND_MAX);
        // printf("key:%s val:%.3f\n", tmp->key, tmp->value);
        push_front(ll_t, tmp);
    }
    print_doubly_ll(ll_t);
    printf("\n");

    cons c = pop_front(ll_t);
    printf("popped from front: cons that has a record of (%s, %.3f)\n", c.rec_t->key, c.rec_t->value);
    print_doubly_ll(ll_t);
    c = pop_back(ll_t);
    printf("popped from back: cons that has a record of (%s, %.3f)\n", c.rec_t->key, c.rec_t->value);
    print_doubly_ll(ll_t);
    printf("\n");

    cons_t c_t = find_rec_by_key(ll_t, "moo");
    printf("delete cons that has a record key of which is 'moo'\n");
    delete_cons(ll_t, c_t);
    print_doubly_ll(ll_t);
    
    record_t new_rec_t = make_record("oof", 100.0);
    insert_rec(ll_t, find_rec_by_key(ll_t, "piyo"), new_rec_t);
    print_doubly_ll(ll_t);

    return 0;
}