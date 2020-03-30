#include <stdio.h>
#include "inversion.h"
#include "nth_smallest.h"

int main(void) {
    double arr[] = {2, 3, 8, 6, 1};
    long inv = inversion(arr, 5);
    printf("the number of inversion: %ld\n", inv);    // 5
    double third = nth_smallest(arr, 5, 3);
    printf("the third smallest: %f\n", third);    // 3.000000
    return 0;
}