#include <stdio.h>
#include "linked.h"


int main(void) {
    LinkedList_t ll_t = make_empty_linked_list();
    print_linked_list(ll_t);    // LinkedList: 
    printf("\n");

    push(ll_t, 8.6);
    push(ll_t, 2.9);
    push(ll_t, 5.5);
    print_linked_list(ll_t);    // LinkedList: [5.500(@0x7ffa66c018c0), next:0x7ffa66c018b0] [2.900(@0x7ffa66c018b0), next:0x7ffa66c018a0] [8.600(@0x7ffa66c018a0), next:0x0] 
    printf("\n");
    printf("search for 8.6: [%.3f, next:%p]", find(ll_t, 8.6)->num, find(ll_t, 8.6)->next);
    printf("\n");

    while (!is_empty(ll_t)) {
        printf("popped: %.3f\n", pop(ll_t).num);
        print_linked_list(ll_t);
    }
    printf("\n");
    
    return 0;
}