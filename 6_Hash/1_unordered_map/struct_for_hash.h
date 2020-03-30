#pragma once

typedef struct {
    char* key;
    double value;
} record, *record_t;


struct cell {
    record_t rec_t;
    struct cell* previous;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;    // 空の場合 NULL
    cons_t tail;    // 空の場合 NULL
} DoublyLL, *DoublyLL_t;


typedef struct {
    int size;    // サイズは 1024 で固定
    DoublyLL_t arr[1024];
} chained_hashtab, *chained_hashtab_t;
