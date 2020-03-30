#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** 単方向循環連結リストの実装
 *  
 * ポインタの参照の循環を効率よく実装するために tail 属性が必要
 * この tail 属性の処理が各メソッド内で必要になるが、それ以外は基本的に単方向連結リストと変わらない。
 * 
 * (circular であることと関係はないが) tail ポインタを保持していることで連結リスト末尾への値の追加 も O(1) で行えるようになっている。
 * 新たに tail(), push_back() が追加されている。
 * なお、双方向でないため、末尾の要素の削除 pop_back(), 指定した cons の直前への挿入 insert(), 指定した cons の削除 delete() はまだ O(n) かかるので実装されていない。
 * 
 * この時点で連結リストを用いた queue の実装が終わっていることがわかる。
 */



struct cell {
    double num;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;    // 連結リストの先頭のセル (= 最後に追加されたセル) を指すポインタ。空の場合は NULL
    cons_t tail;    // 連結リストの末尾のセル (= 最初に追加されたセル) を指すポインタ。空の場合は NULL
} CircularLL, *CircularLL_t;



CircularLL_t make_empty_circular_ll(void) {
    CircularLL_t ll_t = (CircularLL_t)malloc(sizeof(CircularLL));
    if (ll_t == NULL) {
        fprintf(stderr, "make_empty_circular_ll() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    ll_t->head = NULL;
    ll_t->tail = NULL;
    return ll_t;
}


bool is_empty(CircularLL_t ll_t) {
    return ll_t->head == NULL;
}


void print_circular_ll(CircularLL_t ll_t) {
    printf("CircularLL: ");
    cons_t current_cell_t = ll_t->head;
    // 一周したらストップする
    if (current_cell_t != NULL) {
        do {
            printf("[%.3f(@%p), next:%p] ", current_cell_t->num, current_cell_t, current_cell_t->next);
            current_cell_t = current_cell_t->next;
        } while (current_cell_t != ll_t->head);
    }
    printf("\n");
}


void push_front(CircularLL_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push_front() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    if (is_empty(ll_t)) {
        ll_t->tail = c_t;
    }
    // 追加するセルの設定
    c_t->num = x;
    c_t->next = ll_t->head;
    // 挿入セルの前のセルの調整
    ll_t->tail->next = c_t;
    // 現在の head ポインタを挿入セルに向ける
    ll_t->head = c_t;
}

cons pop_front(CircularLL_t ll_t) {
    // 要素数 0 の時はエラー
    if (is_empty(ll_t)) {
        fprintf(stderr, "pop_front() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    cons_t tmp = ll_t->head;
    // 要素数 1 の時
    if (ll_t->head == ll_t->tail) {
        ll_t->head = NULL;
        ll_t->tail = NULL;
    // 要素数 2 以上の時
    } else {
        // 削除セルの前のセルの調整
        ll_t->tail->next = ll_t->head->next;
        // 現在の head ポインタを削除セルの次のセルに向ける
        ll_t->head = ll_t->head->next;
    }
    return *tmp;
}


void push_back(CircularLL_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push_back() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    if (is_empty(ll_t)) {
        ll_t->head = c_t;
        ll_t->tail = c_t;
    }
    // 追加するセルの設定
    c_t->num = x;
    c_t->next = ll_t->head;
    // 挿入セルの前のセルの調整
    ll_t->tail->next = c_t;
    // 現在の tail ポインタを挿入セルに向ける
    ll_t->tail = c_t;
}


cons head(CircularLL_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "head() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    return *(ll_t->head);
}


cons tail(CircularLL_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "tail() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    return *(ll_t->tail);
}


/*
指定値 x が LL 内に存在するか調べ、存在するならそのセルのポインタを、存在しないなら NULL を返す
*/
cons_t find(CircularLL_t ll_t, double x) {
    if (!is_empty(ll_t)) {
        cons_t current_cell_t = ll_t->head;
        while (current_cell_t != ll_t->tail) {
            if (current_cell_t->num == x) return current_cell_t;
            current_cell_t = current_cell_t->next;
        }
        if (current_cell_t->num == x) return current_cell_t;
    }
    return NULL;
}