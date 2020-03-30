#include <stdio.h>
#include <stdlib.h>

/** いわゆる比較ソートの実装
 * 
 * bubble sort, insert sort, select sort, merge sort, quick sort が実装されている。
 * ソートの対象は double num を long n 個要素にもつ配列と仮定している。
 * 前半 3 つの計算量は O(n^2), 後半 2 つの計算量は O(nlgn)
 */


void print_array(double arr[], long n) {
    for (long i=0; i<n; i++) {
        printf("%.3f", arr[i]);
        if (i != n-1) {
            printf(" ");
        }
    }
    printf("\n");
}


void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


/* O(n^2) 比較ソート */

void bubble_sort(double* arr, long n) {
    for (long i=0; i<n; i++) {
        for (long j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr+j, arr+j+1);
            }
        }
    }
}


void insert_sort(double arr[], long n) {
    for (long i=1; i<n; i++) {
        double key = arr[i];
        long j = i-1;
        while (j>=0 && arr[j]>key) {
            arr[j+1] = arr[j];
            j--;
        }
        j++;    // 最後の余分なデクリメント分
        arr[j] = key;
    }
}


void select_sort(double arr[], long n) {
    for (long i=0; i<n; i++) {
        double min = __LONG_MAX__;
        long min_ind;
        for (long j=i; j<n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_ind = j;
            }
        }
        swap(arr+i, arr+min_ind);
    }
}


/* O(nlgn) 比較ソート */


/* 
arr の中で、left_start...left_end, left_end+1...right_end はそれぞれ整列ずみ
left_start...right_end までが整列ずみになるように変更する
*/
void merge(double arr[], long left_start, long left_end, long right_end) {
    long right_start = left_end + 1;
    // 配列の長さ + 1 (番兵) 分とる
    double* buf_1 = malloc(sizeof (double) * (left_end - left_start + 2));
    double* buf_2 = malloc(sizeof (double) * (right_end - right_start + 2));
    // 番兵のセット
    buf_1[left_end-left_start+1] = __LONG_MAX__;
    buf_2[right_end-right_start+1] = __LONG_MAX__;
    // buf への copy
    for (long i=0; i<(left_end-left_start+1); i++) {
        buf_1[i] = arr[left_start+i];
    }
    for (long j=0; j<(right_end-right_start+1); j++) {
        buf_2[j] = arr[right_start+j];
    }
    // buf_1, buf_2 の top を比較して小さい方を順にもとの arr の位置に置いていく
    long i = 0;
    long j = 0;
    long length = right_end - left_start + 1;
    for (long ind=0; ind<length; ind++) {
        if (buf_1[i] < buf_2[j]) {
            arr[left_start+ind] = buf_1[i];
            i++;
        } else {
            arr[left_start+ind] = buf_2[j];
            j++;
        }
    }
    free(buf_1);
    free(buf_2);
}


/*
i: start index, j: end index
i...j までを merge を用いて再帰的に整列する
*/
void merge_sort(double arr[], long i, long j) {
    long mid = (i + j) / 2;
    // i == j となったら再帰の底。そのまま何もせず返す。
    if (i < j) {
        merge_sort(arr, i, mid);
        merge_sort(arr, mid+1, j);
        merge(arr, i, mid, j);
    }
}


/* 
(arr[j] 未満) arr[j] (arr[j] 以上) という形で並ぶようにする
arr[j] がおさまった位置のインデックスを返す。
*/
long partition(double arr[], long i, long j) {
    // buf_head: arr[j] 未満をためているバッファの先頭インデックス。最初は i-1。buf_head+1 <= x < scout なる x は arr[j] 以上である。
    // scout: 常に未探索部の先頭にいる斥候のインデックス。最初は i。こいつを i...j-1 で動かす (最後は arr[j] 自身なのでどうせ arr[j] 未満ではない)。
    long buf_head = i - 1;
    double key = arr[j];
    for (long scout=i; scout<j; scout++) {
        if (arr[scout] < key) {
            buf_head++;
            swap(arr+buf_head, arr+scout);
        }
    }
    buf_head++;
    swap(arr+buf_head, arr+j);
    return buf_head;
}


/* ランダムに選択された要素 x について (x 未満) x (x 以上) という形で並ぶようにする */
long randomized_partition(double arr[], long i, long j) {
    long pivot = (long)rand() % (j-i+1) + i;
    swap(arr+pivot, arr+j);
    return partition(arr, i, j);
}


/*
i: start index, j: end index
i...j までを randomized_partition を用いて再帰的に整列する
*/
void quick_sort(double arr[], long i, long j) {
    if (i < j) {
        long pivot = randomized_partition(arr, i, j);
        quick_sort(arr, i, pivot-1);
        quick_sort(arr, pivot+1, j);
    }
}

