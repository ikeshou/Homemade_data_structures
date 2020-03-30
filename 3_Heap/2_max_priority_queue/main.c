#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "max_pqueue.h"


int main(void) {
    pqueue_t p_t = make_empty_pqueue();
    print_pqueue(p_t);
    printf("\n");

    srand(time(NULL));
    for (int i=0; i<10; i++) {
        record tmp = {'a'+i, ((double)rand()/RAND_MAX) * 100};
        max_pqueue_insert(p_t, tmp);
    }
    print_pqueue(p_t);
    record peeked = peek_maximum(p_t);
    printf("peeked! name=%c, key=%.3f\n", peeked.name, peeked.key);
    printf("\n");

    while (!(is_empty(p_t))) {
        record popped = extract_max(p_t);
        printf("extracted: name=%c, key=%.3f\n", popped.name, popped.key);
        print_pqueue(p_t);
    }
    printf("\n");
    return 0;
}