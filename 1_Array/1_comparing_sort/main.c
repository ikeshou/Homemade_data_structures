#include <time.h>
#include <stdlib.h>
#include "sort.h"


int main(void) {
    double arr[10];
    srand(time(NULL));
    for (int i=0; i<10; i++) {
        arr[i] = (double)rand() / RAND_MAX;
    }
    print_array(arr, 10);

    // printf("bubble sort\n");
    // bubble_sort(arr, 10);

    // printf("insert sort\n");
    // insert_sort(arr, 10);

    // printf("select sort\n");
    // select_sort(arr, 10);

    // printf("merge sort\n");
    // merge_sort(arr, 0, 9);

    // printf("quick sort\n");
    quick_sort(arr, 0, 9);
    
    print_array(arr, 10);
    return 0;
}
