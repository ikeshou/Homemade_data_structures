#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "binary_search.h"


int ascend(const void*, const void*);


int main(void) {
    // binary search
    long arr[15];
    srand(time(NULL));
    for (int i=0; i<15; i++) {
        arr[i] = rand() % 10;
    }
    qsort(arr, 15, sizeof(long), ascend);
    print_array(arr, 15);
    printf("the position of '5' is: %ld\n", binary_search(arr, 0, 14, 5));
    
    // lower_bound
    for (int i=0; i<15; i++) {
        arr[i] = rand() % 50;
    }
    qsort(arr, 15, sizeof(long), ascend);
    print_array(arr, 15);
    printf("the position of the lower bound of '10' is: %ld\n", lower_bound(arr, 0, 14, 10));    // 初めて 10 以上になる要素の index
    printf("the position of the lower bound of '100' is: %ld\n", lower_bound(arr, 0, 14, 100));    // 初めて 100 以上になる要素の index, -1
    
    printf("the position of the upper bound of '10' is: %ld\n", upper_bound(arr, 0, 14, 10));    // 初めて 10 より上になる要素の index
    printf("the position of the upper bound of '100' is: %ld\n", upper_bound(arr, 0, 14, 100));    // 初めて 100 より上になる要素の index, -1
    return 0;
}


// 普通に return *(long*)a - *(long*)b とか書くと int 型のオーバーフローが起きるのでだめ
// しっかり long は long で処理して比較結果を返すようにする
int ascend(const void *a, const void *b) {
    long *A = (long*) a;
    long *B = (long*) b;
    if (*A > *B) return 1;
    if (*A < *B) return -1;
    return 0; 
}