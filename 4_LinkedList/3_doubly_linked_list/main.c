#include <stdio.h>
#include "doubly.h"


int main(void) {
    DoublyLL_t ll_t = make_empty_doubly_ll();
    print_doubly_ll(ll_t);
    printf("\n");

    push_front(ll_t, 4.3);
    // print_doubly_ll(ll_t);
    push_front(ll_t, 3.2);
    // print_doubly_ll(ll_t);
    push_front(ll_t, 2.1);
    // print_doubly_ll(ll_t);
    push_front(ll_t, 1.0);
    // print_doubly_ll(ll_t);
    push_back(ll_t, 5.4);
    print_doubly_ll(ll_t);
    printf("search for 5.4: [%.3f, next:%p]\n", find(ll_t, 5.4)->num, find(ll_t, 5.4)->next);
    printf("insert 6.5 cell before 5.4 cell\n");
    insert(ll_t, find(ll_t, 5.4), 6.5);
    print_doubly_ll(ll_t);
    printf("delete 5.4 cell\n");
    delete(ll_t, find(ll_t, 5.4));
    print_doubly_ll(ll_t);
    printf("\n");
    
    printf("head: [%.3f, next:%p]\n", head(ll_t).num, head(ll_t).next);
    pop_front(ll_t);
    printf("popped from front.\n");
    print_doubly_ll(ll_t); 
    printf("tail: [%.3f, next:%p]\n", tail(ll_t).num, tail(ll_t).next);
    pop_back(ll_t);
    printf("popped from back.\n");
    print_doubly_ll(ll_t);
    printf("\n");

    while (!is_empty(ll_t)) {
        cons popped = pop_front(ll_t);
        printf("popped: [%.3f, next:%p]\n", popped.num, popped.next);
        print_doubly_ll(ll_t);
    }
    printf("\n");

    return 0;
}