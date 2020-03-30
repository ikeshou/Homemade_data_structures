#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "hash_func.h"


int main(void) {
    printf("ascii_to_int_base_128(%s): %d\n", "ab", ascii_to_int_base_128("ab"));    // 12514
    printf("int_to_ascii_to_int(%d): %d\n", 12, int_to_ascii_to_int(12));    // 6322

    printf("devision_hash(5000): %d\n",  devision_hash(5000));    // 93 (しっかり 701 未満！)
    printf("multiplication_hash(5000): %d\n", multiplication_hash(5000));    // 174 (しっかり 1024 未満！)
    
    printf("%d\n", devision_hash(ascii_to_int_base_128("hoge")));    // 472
    printf("%d\n", devision_hash(ascii_to_int_base_128("::")));    // hash 値 7482 % 701 = 472 で衝突するケース

    printf("%d\n", multiplication_hash(7.7));    // 777
    printf("%d\n", multiplication_hash(519.0));    // 777 で衝突するケース
    
    printf("start assertion test...!\n");
    for (int i=0; i<INT_MAX; i++) {
        int tmp = devision_hash(i);
        assert(0 <= tmp && tmp < 701);
        int tmp2 = multiplication_hash(i);
        assert(0 <= tmp2 && tmp2 < 1024);
    }
    printf("assertion test is finished successfully\n");

    return 0;
}