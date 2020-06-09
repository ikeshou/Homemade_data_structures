#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>


/** いわゆる最大優先度キューの実装
 * 
 * 対象は char name と double key を属性にもつ構造体を long n 個要素にもつような配列を仮定した。
 * 収納するものが構造体になり、そのキー (優先度を表しているつもり) でもって二分木を構成するというだけで、他は全て max heap の時と同じ。
 */



#define LEFT(i) (((i)<<(1)) + (1))
#define RIGHT(i) (((i)<<(1)) + (2))
#define PARENT(i) (((i)-(1)) >> (1))


typedef struct {
    char name;
    double key;
} record, *record_t;


/* max-pqueue */
typedef struct {
    long size;
    long max_size;
    record* arr;
} pqueue, *pqueue_t;


void swap(record_t a, record_t b) {
    record tmp = *a;
    *a = *b;
    *b = tmp;
}


pqueue_t make_empty_pqueue(void) {
    pqueue_t p_t = (pqueue_t)malloc(sizeof(pqueue));
    if (p_t == NULL) {
        fprintf(stderr, "build_max_pqueue() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }    
    p_t->size = 0;
    p_t->max_size = 100;
    p_t->arr = (record_t)malloc(sizeof(record) * 100);
    if (p_t->arr == NULL) {
        fprintf(stderr, "build_max_pqueue() in %s: cannot allocate enough memory\n", __FILE__);
        exit(-1);
    }
    return p_t;
}


void print_pqueue(pqueue_t p_t) {
    printf("pqueue: ");
    for (long i=0; i<(p_t->size); i++) {
        if (i != 0) printf(" ");
        printf("{%c:%.3f}", (p_t->arr)[i].name, (p_t->arr)[i].key);
    }
    printf("\n");
}


bool is_empty(pqueue_t p_t) {
    return p_t->size == 0;
}


void expand_pqueue(pqueue_t p_t, long n) {
    record_t ptr = (record_t)realloc(p_t->arr, sizeof(record) * n);
    if (ptr == NULL) {
        fprintf(stderr, "expand_pqueue() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    p_t->arr = ptr;
}


void max_pqueate(pqueue_t p_t, long i) {
    long l = LEFT(i);
    long r = RIGHT(i);
    long largest = i;
    // printf("i: %ld\n", i);
    if (l < p_t->size && (p_t->arr)[l].key > (p_t->arr)[largest].key) {
        largest = l;
    }
    if (r < p_t->size && (p_t->arr)[r].key > (p_t->arr)[largest].key) {
        largest = r;
    }
    if (largest != i) {
        swap((p_t->arr)+i, (p_t->arr)+largest);
        max_pqueate(p_t, largest);
    }
    // print_heap(h_t);
}


record peek_maximum(pqueue_t p_t) {
    if (p_t->size == 0) {
        fprintf(stderr, "peek_maximum() in %s: pqueue is empty\n", __FILE__);
        exit(-1);
    }
    return (p_t->arr)[0];
}


void max_pqueue_increase_key(pqueue_t p_t, long i, double new_key) {
    if (p_t->size <= i) {
        fprintf(stderr, "max_pqueue_change_num() in %s: out of range\n", __FILE__);
        exit(-1);
    }
    // 値を減らす時
    if ((p_t->arr)[i].key > new_key) {
        fprintf(stderr, "max_pqueue_increase_num() in %s: cannot decrease key\n", __FILE__);
        exit(-1);
        // (p_t->arr)[i].key = new_key;
        // max_pqueate(p_t, i);
    // 値を増やす時
    } else if ((p_t->arr)[i].key < new_key) {
        (p_t->arr)[i].key = new_key;
        // 親が存在し、ヒープ条件が壊れている時
        while (i >= 1 && (p_t->arr)[i].key > (p_t->arr)[PARENT(i)].key) {
            swap(p_t->arr+i, p_t->arr+PARENT(i));
            i = PARENT(i);
        }
    }
    // 値を変えぬ時は何もしなくて良い
}


void max_pqueue_insert(pqueue_t p_t, record rec) {
    if (p_t->size + 1 > p_t->max_size) {
        fprintf(stderr, "max_pqueue_insert() in %s: pqueue is full.\n", __FILE__);
        exit(-1);
    }
    p_t->size++;
    record tmp = {rec.name, - DBL_MAX};
    (p_t->arr)[p_t->size - 1] = tmp;    // この段階では確かに max-heap 条件を満たしている
    max_pqueue_increase_key(p_t, p_t->size - 1, rec.key);    // その -inf を rec.key へと値を変更してやるだけ
}


record extract_max(pqueue_t p_t) {
    if (p_t->size == 0) {
        fprintf(stderr, "extract_max() in %s: pqueue is empty\n", __FILE__);
        exit(-1);
    }
    record max = (p_t->arr)[0];
    swap(p_t->arr, p_t->arr + p_t->size -1);
    p_t->size--;
    max_pqueate(p_t, 0);
    return max;
}