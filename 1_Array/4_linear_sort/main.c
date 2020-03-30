#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stable_counting.h"

int main(void) {
    Card deck[] = {{'H', 3}, {'D', 10}, {'C', 11}, {'S', 1}, 
                   {'H', 7}, {'D', 7}, {'C', 7}, {'S', 7},
                   {'D', 4}, {'D', 5}, {'D', 6}, {'D', 7}};
    printf("\nstable counting sort with struct!\n");
    print_trump_array(deck, 12);    // H3 D10 C11 S1 H7 D7 C7 S7 D4 D5 D6 D7 
    counting_sort_trump(deck, 12);
    print_trump_array(deck, 12);    // S1 H3 D4 D5 D6 H7 D7 C7 S7 D7 D10 C11
    
    printf("\nstable counting sort with ordinary array of long int!\n");
    long arr[10];
    srand(time(NULL));
    for (int i=0; i<10; i++) {
        arr[i] = (long) rand() % 5;
    }
    print_long_array(arr, 10);
    counting_sort(arr, 10, 4);
    print_long_array(arr, 10);

    printf("\nstable radix sort with ordinary array of long int (1000-9999)!\n");
    long decimal_system_arr[12];
    for (int i=0; i<12; i++) {
        decimal_system_arr[i] = (1000 + (long)((double)rand() * (9999-1000) / RAND_MAX));
    }
    print_long_array(decimal_system_arr, 12);
    radix_sort(decimal_system_arr, 12, 4);
    print_long_array(decimal_system_arr, 12);
    return 0;
}