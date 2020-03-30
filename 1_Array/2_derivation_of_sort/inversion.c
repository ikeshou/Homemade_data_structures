#include <stdio.h>
#include <stdlib.h>

/** 配列の転置数を求めるプログラムの実装
 * 
 * 対象は double num を long n 個要素としてもつ配列を仮定している。
 * 内部で merge_sort の関数 (に少し手を加えたもの) を使用する。
 * 計算量は O(nlgn)
 */



/*
left_start...left_end, left_end+1...right_end はそれぞれ整列ずみ
left_start...right_end までが整列ずみになるように変更する。
その際、反転数 inversion を計算しておき最後に返す。
*/
long modified_merge(double arr[], long left_start, long left_end, long right_end) {
    long right_start = left_end + 1;
    double* buf_1 = malloc(sizeof (double) * (left_end - left_start + 2));    // 配列の長さ + 1 (番兵) 分とる
    double* buf_2 = malloc(sizeof (double) * (right_end - right_start + 2));
    // 番兵のセット
    buf_1[left_end-left_start+1] = __LONG_LONG_MAX__;
    buf_2[right_end-right_start+1] = __LONG_LONG_MAX__;
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
    long inv = 0;
    long length = right_end - left_start + 1;
    for (long ind=0; ind<length; ind++) {
        if (buf_1[i] < buf_2[j]) {
            arr[left_start+ind] = buf_1[i];
            i++;
            inv += j;    // 左のデック (buf_2) のカードがそれぞれ積まれたとき、すでに積まれていた右のデックのカードの枚数を足していく
        } else {
            arr[left_start+ind] = buf_2[j];
            j++;
        }
    }
    free(buf_1);
    free(buf_2);
    return inv;
}


/*
i: start index, j: end index
i...j までを整列する
反転数 inversion を計算して返す
*/
long modified_merge_sort(double arr[], long i, long j) {
    long inv_left, inv_right, inv_last;
    long mid = (i + j) / 2;
    // i == j となったら再帰の底。そのまま何もせず返す。
    if (i < j) {
        inv_left = modified_merge_sort(arr, i, mid);
        inv_right = modified_merge_sort(arr, mid+1, j);
        inv_last = modified_merge(arr, i, mid, j);
        return inv_left + inv_right + inv_last;
    } else {
        return 0;
    }
}


/* 
もとの配列を変更されないようにコピーを生成しておき、それに対してマージソートをしながら反転数を数える
もちろん O(nlgn)
*/
long inversion(double arr[], long n){
    long ans;
    double* tmp = malloc(sizeof (double) * n);
    for (long i=0; i<n; i++) {
        tmp[i] = arr[i];
    }
    ans = modified_merge_sort(tmp, 0, n-1);
    free(tmp);
    return ans;
}