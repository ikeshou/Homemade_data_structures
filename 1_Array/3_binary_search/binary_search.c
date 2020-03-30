#include <stdio.h>

/** いわゆる二分探索の実装
 * 
 * 対象は long num を long n 個要素にもつソートずみ配列であると仮定する。
 * ピンポイントで同じ値の要素を探索する binary_search(),
 * 初めて指定した値以上となる要素を探索する lower_bind(),
 * 初めて指定した値より大きくなる要素を探索する upper_bind() 
 * の 3 つを実装。
 * 計算量は O(lgn)
 */


void print_array(long arr[], long n) {
    for (long i=0; i<n; i++) {
        printf("%ld", arr[i]);
        if (i != n-1) {
            printf(" ");
        }
    }
    printf("\n");
}



long binary_search(long arr[], long i, long j, long num) {
    /* arr はソートずみ配列
       num が arr に存在するとき、その index を返す。存在しない場合 -1 を返す。 */
    // 再帰の底
    if (i > j) return -1;

    long mid = (i + j) / 2;
    double key = arr[mid];
    if (num < key) {
        return binary_search(arr, i, mid-1, num);
    } else if (key < num) {
        return binary_search(arr, mid+1, j, num);
    } else {
        return mid;
    }
}


long lower_bound(long arr[], long i, long j, long num) {
    /* 初めて num 以上となる要素の index を返す。存在しない場合 -1 を返す。 */
    // 再帰の底
    if (i > j) {
        return -1;
    } else if (i == j && arr[i] < num) {
        return -1;
    }
    if (arr[i] >= num) return i;

    long mid = (i + j) / 2;
    double key = arr[mid];
    if (num <= key) {
        return lower_bound(arr, i, mid, num);
    } else {
        return lower_bound(arr, mid+1, j, num);
    }
}


long upper_bound(long arr[], long i, long j, long num) {
    /* 初めて num より大きくなる要素の index を返す。存在しない場合 -1 を返す。 */
    // 再帰の底
    if (i > j) {
        return -1;
    } else if (i == j && arr[i] <= num) {
        return -1;
    } 
    if (arr[i] > num) return i;

    long mid = (i + j) / 2;
    double key = arr[mid];
    if (num < key) {
        return upper_bound(arr, i, mid, num);
    } else {
        return upper_bound(arr, mid+1, j, num);
    }
}