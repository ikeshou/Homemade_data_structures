#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** n 番目に小さい数 (順序統計量) を求めるプログラムの実装
 * 
 * 対象は double num を long n 個要素としてもつ配列を仮定している。
 * 内部で quick_sort の関数 (に手を加えたもの)　を使用する。
 * 計算量は O(n)
 */


void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


/*
(arr[j] 未満) arr[j] (arr[j] 以上) という形で並ぶようにする
arr[j] がおさまった位置のインデックスを返す。
*/
long partition(double arr[], long i, long j) {
    // buf_head: arr[j] 未満をためているバッファの先頭インデックス。最初は i-1。buf_head+1 <= x < scout なる x は arr[j] 以上である。
    // scout: 常に未探索部の先頭にいる斥候のインデックス。最初は i。こいつを i...j-1 で動かす (最後は arr[j] 自身なのでどうせ arr[j] 未満ではない)。
    double key = arr[j];
    long buf_head = i - 1;
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


/*
ランダムに選択された要素 x について (x 未満) x (x 以上) という形で並ぶようにする。
arr[j] がおさまった位置のインデックスを返す。
*/
long randomized_partition(double arr[], long i, long j) {
    long pivot = (long)rand() % (j-i+1) + i;
    swap(arr+pivot, arr+j);
    return partition(arr, i, j);
}


/*
arr の中で k+1 番目に小さい要素を返す (もし小さい順に整列したとき index が k となる要素)
毎回片方しか実行されない quick sort のようなもの
arr のうち 0-index で k となる値を含まない部分配列については処理を行わず切り捨てていく
*/
double modified_quick_sort(double arr[], long i, long j, long k) {
    assert(i <= j);
    if (i < j) {
        long pivot = randomized_partition(arr, i, j);
        if (k < pivot) {
            return modified_quick_sort(arr, i, pivot-1, k);
        } else if (pivot < k) {
            return modified_quick_sort(arr, pivot+1, j, k);
        } else {
            return arr[pivot];
        }
    } else {
        return arr[i];
    }
}


/*
k 番目に小さい要素を返す O(n) アルゴリズム
もとの配列を変更されないようにコピーを作成。
コピーに対し modified_quick_sort をかけて枝刈りをしつつ探索していく。
*/
double nth_smallest(double arr[], long length, long k) {
    assert(length >= k);
    double* tmp = malloc(sizeof (double) * length);
    double ans;
    for (long i=0; i<length; i++) {
        tmp[i] = arr[i];
    }
    ans = modified_quick_sort(tmp, 0, length-1, k-1);
    free(tmp);
    return ans;
}