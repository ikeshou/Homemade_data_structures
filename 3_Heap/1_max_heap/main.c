#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

#define PARENT(i) (((i)-(1)) >> (1))


int main(void) {
    heap_t h_t_1 = make_empty_heap();
    print_heap(h_t_1);
    printf("\n");
    // peek_maximum(h_t_1);
    free(h_t_1->arr);
    free(h_t_1);
    
    double arr[8] = {1.2, 1.5, 9.3, 8.3, 6.6, 7.7, 3.2, 9.9};
    heap_t h_t_2 = build_max_heap(arr, 8);
    print_heap(h_t_2);    // heap: 9.900 8.300 9.300 1.500 6.600 7.700 3.200 1.200
    printf("%f\n", peek_maximum(h_t_2));    // 9.900000
    printf("\n");

    while (!(is_empty(h_t_2))) {
        printf("%f\n", extract_max(h_t_2));
        print_heap(h_t_2);
    }
    printf("\n");

    srand(time(NULL));
    for (int i=0; i<8; i++) max_heap_insert(h_t_2, (double)rand() / RAND_MAX);
    print_heap(h_t_2);

    max_heap_change_num(h_t_2, 0, 0.001);
    print_heap(h_t_2);
    max_heap_change_num(h_t_2, 7, 100.0);
    print_heap(h_t_2);

    while (!(is_empty(h_t_2))) {
        printf("%f\n", extract_max(h_t_2));
        print_heap(h_t_2);
    }
    printf("\n");
    free(h_t_2->arr);
    free(h_t_2);

    heap_sort(arr, 8);
    for (int i=0; i<8; i++) printf("%.3f ", arr[i]);    // 9.900 9.300 8.300 7.700 6.600 3.200 1.500 1.200 
    printf("\n");

    return 0;
}