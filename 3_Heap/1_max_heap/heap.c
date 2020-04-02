#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>


/** いわゆる max heap の実装
 * 
 * 対象は double num を long n 個要素にもつような配列を仮定している。
 * なお、このヒープ構造体はサイズが自動的に伸縮しないため、それ用の関数でサイズを明示的に増やしてやる必要があることに注意。
 * (すでに実装した vector 使えばいけるけれど)
 * 
 * ヒープ条件を満足させるための要である max_heapify(),
 * ヒープを作成するための make_empty_heap(), build_max_heap(),
 * ヒープサイズを拡張するための expand_heap(),
 * 状態を知るための is_empty(), peek_maximum(),
 * ヒープを出力するための print_heap(),
 * ヒープ操作のための max_heap_increase_num(), max_heap_insert(), extract_max()
 * を実装した。
 * max_heapify(), max_heap_increase_num(), max_heap_insert(), extract_max() はいずれも計算量 O(lgn)
 * build_max_heap() は計算量 O(n)
 * 
 * ヒープを用いてソートを行う heap_sort() も実装した。この計算量は O(nlgn)
 */



#define LEFT(i) (((i)<<(1)) + (1))
#define RIGHT(i) (((i)<<(1)) + (2))
#define PARENT(i) (((i)-(1)) >> (1))


/* max-heap */
typedef struct {
    long size;
    long max_size;
    double* arr;
} heap, *heap_t;


void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

// とりあえず固定長で 100 要素分とる
heap_t make_empty_heap(void) {
    heap_t h_t = (heap_t)malloc(sizeof(heap));
    if (h_t == NULL) {
        fprintf(stderr, "build_max_heap() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }    
    h_t->size = 0;
    h_t->max_size = 100;
    h_t->arr = (double*)malloc(sizeof(double) * 100);
    if (h_t->arr == NULL) {
        fprintf(stderr, "build_max_heap() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }
    return h_t;
}


void print_heap(heap_t h_t) {
    printf("heap: ");
    for (long i=0; i<(h_t->size); i++) {
        if (i != 0) printf(" ");
        printf("%.3f", (h_t->arr)[i]);
    }
    printf("\n");
}


bool is_empty(heap_t h_t) {
    return h_t->size == 0;
}


void expand_heap(heap_t h_t, long n) {
    double* ptr = (double*)realloc(h_t->arr, sizeof(double) * n);
    if (ptr == NULL) {
        fprintf(stderr, "expand_heap() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    h_t->arr = ptr;
}


/*
LEFT(i), RIGHT(i) を root とする二分木はどちらも max-heap 条件を満たすとする。
このとき、i を root とする二分木が max-heap 条件を満たすように変更する O(lgn) アルゴリズム
具体的には、arr[i], arr[LEFT(i)], arr[RIGHT(i)] の最大の要素と arr[i] を swap し、swap が生じたらその部分木に対して再帰的に max_heapify を呼び出す。
(arr[i] を '滑り落とす')
*/
void max_heapify(heap_t h_t, long i) {
    long l = LEFT(i);
    long r = RIGHT(i);
    long largest = i;
    // printf("i: %ld\n", i);
    if (l < h_t->size && (h_t->arr)[l] > (h_t->arr)[largest]) {
        largest = l;
    }
    if (r < h_t->size && (h_t->arr)[r] > (h_t->arr)[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap((h_t->arr)+i, (h_t->arr)+largest);
        max_heapify(h_t, largest);
    }
    // print_heap(h_t);
}


/*
配列 arr[0...n-1] から max-heap を作成し、そのポインタを返す O(n) アルゴリズム
呼び出し元がこのポインタ h_t の解放と、h_t->arr の解放を担う
固定長で n 分要素を確保するが、それを超える分については保存不可能なことに注意
*/
heap_t build_max_heap(double* A, long n) {
    heap_t h_t = (heap_t)malloc(sizeof(heap));
    if (h_t == NULL) {
        fprintf(stderr, "build_max_heap() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }
    h_t->size = n;
    h_t->max_size = n;
    h_t->arr = (double*)malloc(sizeof(double) * n);
    if (h_t->arr == NULL) {
        fprintf(stderr, "build_max_heap() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }
    for (long i=0; i<n; i++) {
        (h_t->arr)[i] = A[i];
    }
    for (long i=PARENT(n-1); i>=0; i--) {
        max_heapify(h_t, i);
    }
    return h_t;
}


/*
max-heap の最大値を盗み見る O(1) アルゴリズム
*/
double peek_maximum(heap_t h_t) {
    if (h_t->size == 0) {
        fprintf(stderr, "peek_maximum() in %s: heap is empty\n", __FILE__);
        exit(-1);
    }
    return (h_t->arr)[0];
}


/*
max-heap のあるインデックスの値を増やす O(lgn) アルゴリズム
減らすのは完全二分木が崩れるので NG
*/
void max_heap_increase_num(heap_t h_t, long i, double num) {
    if (h_t->size <= i) {
        fprintf(stderr, "max_heap_increase_num() in %s: out of range\n", __FILE__);
        exit(-1);
    }
    // 値を減らす時
    if ((h_t->arr)[i] > num) {
        fprintf(stderr, "max_heap_increase_num() in %s: cannot decrease value\n", __FILE__);
        exit(-1);
        // (h_t->arr)[i] = num;
        // max_heapify(h_t, i);
    // 値を増やす時
    } else if ((h_t->arr)[i] < num) {
        (h_t->arr)[i] = num;
        // 親が存在し、ヒープ条件が壊れている時
        while (i >= 1 && (h_t->arr)[i] > (h_t->arr)[PARENT(i)]) {
            swap(h_t->arr+i, h_t->arr+PARENT(i));
            i = PARENT(i);
        }
    }
    // 値を変えぬ時は何もしなくて良い
}

/*
max-heap に値を追加する O(lgn) アルゴリズム
*/
void max_heap_insert(heap_t h_t, double num) {
    if (h_t->size + 1 > h_t->max_size) {
        fprintf(stderr, "max_heap_insert() in %s: heap is full.\n", __FILE__);
        exit(-1);
    }
    h_t->size++;
    (h_t->arr)[h_t->size - 1] = - DBL_MAX;    // この段階では確かに max-heap 条件を満たしている
    max_heap_increase_num(h_t, h_t->size - 1, num);    // その -inf を num へと値を変更してやるだけ
}


/*
max-heap から最大値を取り出して返す O(lgn) アルゴリズム
*/
double extract_max(heap_t h_t) {
    if (h_t->size == 0) {
        fprintf(stderr, "extract_max() in %s: heap is empty\n", __FILE__);
        exit(-1);
    }
    double max = (h_t->arr)[0];
    swap(h_t->arr, h_t->arr + h_t->size -1);
    h_t->size--;
    max_heapify(h_t, 0);
    return max;
}


/*
降順 heapsort を O(nlgn) で行う
具体的には heap 構築 -> 要素がなくなるまで extract_max を行っている
*/
void heap_sort(double* arr, long n) {
    heap_t h_t = build_max_heap(arr, n);
    for (long i=0; i<n; i++) {
        arr[i] = extract_max(h_t);
    }
    free(h_t->arr);
    free(h_t);
}