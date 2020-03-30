#include <stdio.h>
#include <stdlib.h>
#include "deque.h"


int main(void) {
    deque_t deq_t = make_deque();
    print_deque(deq_t);    // capacity: 4, number of element: 0, start: -1, end: -1 buffer: 0.000 0.000 0.000 0.000
    traverse_deque(deq_t);    // deque contents:
    push_back(deq_t, 1.0);
    print_deque(deq_t);    // capacity: 4, number of element: 1, start: 0, end: 0 buffer: 1.000 0.000 0.000 0.00
    traverse_deque(deq_t);    // deque contents: 1.000 
    push_back(deq_t, 2.0);
    print_deque(deq_t);    // capacity: 4, number of element: 2, start: 0, end: 1 buffer: 1.000 2.000 0.000 0.000
    traverse_deque(deq_t);    // deque contents: 1.000 2.000 
    push_front(deq_t, 4.0);
    print_deque(deq_t);    // capacity: 4, number of element: 3, start: 3, end: 1 buffer: 1.000 2.000 0.000 4.000
    traverse_deque(deq_t);    // deque contents: 4.000 1.000 2.000 
    push_front(deq_t, 3.0);
    print_deque(deq_t);    // capacity: 4, number of element: 4, start: 2, end: 1 buffer: 1.000 2.000 3.000 4.000
    traverse_deque(deq_t);    // deque contents: 3.000 4.000 1.000 2.000
    pop_front(deq_t);
    print_deque(deq_t);    // capacity: 4, number of element: 3, start: 3, end: 1 buffer: 1.000 2.000 3.000 4.000 (メモリは上書きされぬ)
    traverse_deque(deq_t);    // deque contents: 4.000 1.000 2.000
    push_front(deq_t, 5.0);
    print_deque(deq_t);    // capacity: 4, number of element: 4, start: 2, end: 1 buffer: 1.000 2.000 5.000 4.000 
    traverse_deque(deq_t);    // deque contents: 5.000 4.000 1.000 2.000

    /* リングバッファの拡張が生じる */
    push_back(deq_t, 3.0);
    print_deque(deq_t);    // capacity: 8, number of element: 5, start: 0, end: 4 buffer: 5.000 4.000 1.000 2.000 3.000 0.000 0.000 0.000 (しっかり再配置される)
    traverse_deque(deq_t);    // deque contents: 5.000 4.000 1.000 2.000 3.000

    printf("position of '[4]' is: %.3f\n", at(deq_t, 4));    // position of '[4]' is: 3.000
    printf("\n");

    while (!is_empty(deq_t)) {
        double popped = pop_front(deq_t);
        printf("popped from front: %.3f\n", popped);
        print_deque(deq_t);
        traverse_deque(deq_t);
    }
    printf("\n");

    free(deq_t->arr);
    free(deq_t);
    
    return 0;
}
