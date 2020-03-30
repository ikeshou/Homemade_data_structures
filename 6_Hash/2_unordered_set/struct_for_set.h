#pragma once

struct cell {
    double num;
    struct cell* previous;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;    // 連結リストの先頭のセル (= 最後に追加されたセル) を指すポインタ。空の場合は NULL
    cons_t tail;    // 連結リストの先頭のセル (= 最後に追加されたセル) を指すポインタ。空の場合は NULL
} DoublyLL, *DoublyLL_t;


typedef struct {
    int size;    // テーブル全体のサイズ (1024 で固定)
    DoublyLL_t arr[1024];
} chained_hashtab, *chained_hashtab_t;
