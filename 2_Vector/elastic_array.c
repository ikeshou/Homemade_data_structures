#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** いわゆる C++ でいうところの vector の実装
 * 
 * 今回はコンテナの収納対象は double とした。
 * 作成のための make_vector(),
 * 値の追加削除のための push_back(), pop_back(),
 * ランダムアクセスのための at(), front(), back(),
 * ポインタ取得のための begin(), end(),
 * 要素表示のための print_vector(),
 * ベクターの状態を知るための empty(), capacity(), size()
 * を実装した。
 * 
 * 追加で配列の容量が足りなくなるたびに、今までの 2 倍のメモリ領域となるよう新たにヒープにメモリを確保する。
 * 
 * この時点で動的配列を用いた stack の実装が完了していることがわかる。(リングバッファを使うまでもない)
 */


typedef struct {
    long capacity; // 拡張なく入れることのできる要素数
    long size; // 現在の要素数
    double* arr;
} vector, *vector_t;


vector_t make_vector(void) {
    // ここで返された vector について。このポインタを通して free するだけではなく、arr メンバ領域も free する必要があることに注意
    vector_t vec_t = (vector_t)malloc(sizeof(vector));
    vec_t->capacity = 1;
    vec_t->size = 0;
    vec_t->arr = (double*)malloc(sizeof(double));
    if (vec_t->arr == NULL) {
        fprintf(stderr, "make_vector() in %s: cannot allocate an intial memory\n", __FILE__);
        exit(-1);
    } 
    return vec_t;
}


/* 細々としたメンバ関数 */
long capacity(vector_t vec_t) {
    return vec_t->capacity;
}

long size(vector_t vec_t) {
    return vec_t->size;
}

bool is_empty(vector_t vec_t) {
    return (bool)(vec_t->size == 0);
}


/* デバッグ用 */
void print_vector(vector_t vec_t) {
    printf("current capacity: %ld, number of element: %ld\n", capacity(vec_t), size(vec_t));
    printf("vector: ");
    for (long i=0; i<vec_t->size; i++) {
        if (i != 0) printf(" ");
        printf("%.3f", (vec_t->arr)[i]);
    }
    printf("\n");
}


void push_back(vector_t vec_t, const double num) {
    if (vec_t->capacity == vec_t->size) {
        double* ptr = (double*)realloc(vec_t->arr, sizeof(double) * (vec_t->capacity * 2));
        if (ptr == NULL) {
            fprintf(stderr, "push_back() in %s: cannot allocate an extra memory\n", __FILE__);
            exit(-1);
        }
        vec_t->arr = ptr;    // reallocation の結果、ptr の示す先頭アドレスは arr の先頭アドレスと異なることもある
        vec_t->capacity *= 2;
        (vec_t->arr)[vec_t->size] = num;
        vec_t->size++;
    } else {
        (vec_t->arr)[vec_t->size] = num;
        vec_t->size++;
    }
}


void pop_back(vector_t vec_t) {
    if (is_empty(vec_t)) {
        fprintf(stderr, "pop_back() in %s: cannot pop from an empty vector\n", __FILE__);
        exit(-1);
    }
    vec_t->size--;
}


/* cpp の vector だったら参照が返るけど今回は値を返している */
double at(vector_t vec_t, const long ind) {
    if (ind > vec_t->size - 1) {
        fprintf(stderr, "at() in %s: out of range\n", __FILE__);
        exit(-1);
    }
    return (vec_t->arr)[ind];
}

double front(vector_t vec_t) {
    if (is_empty(vec_t)) {
        fprintf(stderr, "front() in %s: vector is empty\n", __FILE__);
        exit(-1);
    }
    return (vec_t->arr)[0];
}

double back(vector_t vec_t) {
    if (is_empty(vec_t)) {
        fprintf(stderr, "front() in %s: vector is empty\n", __FILE__);
        exit(-1);
    }
    return (vec_t->arr)[vec_t->size-1];
}


/* cpp の vector だったらイテレータが返るけど今回はポインタを返している */
double* begin(vector_t vec_t) {
    if (is_empty(vec_t)) {
        fprintf(stderr, "begin() in %s: vector is empty\n", __FILE__);
        exit(-1);
    }
    return vec_t->arr;
}

double* end(vector_t vec_t) {
    if (is_empty(vec_t)) {
        fprintf(stderr, "end() in %s: vector is empty\n", __FILE__);
        exit(-1);
    }
    return vec_t->arr + vec_t->size;    // cpp の end 同様、最後の要素の次を示す。間接参照するとセグフォるはず。
}
