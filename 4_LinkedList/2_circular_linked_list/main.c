#include <stdio.h>
#include "circular.h"

int main(void) {
    CircularLL_t ll_t = make_empty_circular_ll();
    print_circular_ll(ll_t);
    printf("\n");

    push_front(ll_t, 4.3);
    push_front(ll_t, 3.2);
    push_front(ll_t, 2.1);
    push_front(ll_t, 1.0);
    push_back(ll_t, 5.4);
    print_circular_ll(ll_t);
    
    printf("head: [%.3f, next:%p]\n", head(ll_t).num, head(ll_t).next);
    printf("tail: [%.3f, next:%p]\n", tail(ll_t).num, tail(ll_t).next);
    printf("\n");

    printf("search for 5.4: [%.3f, next:%p]\n", find(ll_t, 5.4)->num, find(ll_t, 5.4)->next);
    printf("search for 1.0: [%.3f, next:%p]\n", find(ll_t, 1.0)->num, find(ll_t, 1.0)->next);
    printf("\n");

    while (!is_empty(ll_t)) {
        cons popped = pop_front(ll_t);
        printf("popped: [%.3f, next:%p]\n", popped.num, popped.next);
        print_circular_ll(ll_t);
    }
    printf("\n");

    return 0;
}