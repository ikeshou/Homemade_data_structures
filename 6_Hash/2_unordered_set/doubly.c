#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct_for_set.h"



DoublyLL_t make_empty_doubly_ll(void) {
    DoublyLL_t ll_t = (DoublyLL_t)malloc(sizeof(DoublyLL));
    if (ll_t == NULL) {
        fprintf(stderr, "make_empty_doubly_ll() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    ll_t->head = NULL;
    ll_t->tail = NULL;
    return ll_t;
}


bool is_empty(DoublyLL_t ll_t) {
    return ll_t->head == NULL;
}


void print_doubly_ll(DoublyLL_t ll_t) {
    printf("DoublyLL: [");
    cons_t current_cell_t = ll_t->head;
    while (current_cell_t != NULL) {
        printf("[%.3f(@%p]", current_cell_t->num, current_cell_t);
        current_cell_t = current_cell_t->next;
    }
    printf("] ");
    // printf("\n");
}


void push_front(DoublyLL_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push_front() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    if (is_empty(ll_t)) {
        c_t->num = x;
        c_t->previous = NULL;
        c_t->next = NULL;
        ll_t->head = c_t;
        ll_t->tail = c_t;
    } else {
        // 追加するセルの設定
        c_t->num = x;
        c_t->previous = NULL;
        c_t->next = ll_t->head;
        // 挿入セルの次のセルの調整
        ll_t->head->previous = c_t;
        // 現在の head ポインタを挿入セルに向ける
        ll_t->head = c_t;
    }
}

cons pop_front(DoublyLL_t ll_t) {
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
        // 削除セルの次のセルの調整
        ll_t->head->next->previous = NULL;
        // 現在の head ポインタを削除セルの次のセルに向ける
        ll_t->head = ll_t->head->next;
    }
    return *tmp;
}


void push_back(DoublyLL_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push_back() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    if (is_empty(ll_t)) {
        c_t->num = x;
        c_t->previous = NULL;
        c_t->next = NULL;
        ll_t->head = c_t;
        ll_t->tail = c_t;
    } else {
        // 追加するセルの設定
        c_t->num = x;
        c_t->previous = ll_t->tail;
        c_t->next = NULL;
        // 挿入セルの前のセルの調整
        ll_t->tail->next = c_t;
        // 現在の tail ポインタを挿入セルに向ける
        ll_t->tail = c_t;
    }
}


cons pop_back(DoublyLL_t ll_t) {
    // 要素数 0 の時はエラー
    if (is_empty(ll_t)) {
        fprintf(stderr, "pop_back() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    cons_t tmp = ll_t->tail;
    // 要素数 1 の時
    if (ll_t->head == ll_t->tail) {
        ll_t->head = NULL;
        ll_t->tail = NULL;
    // 要素数 2 以上の時
    } else {
        // 削除セルの前のセルの調整
        ll_t->tail->previous->next = NULL;
        // 現在の tail ポインタを削除セルの前のセルに向ける
        ll_t->tail = ll_t->tail->previous;
    }
    return *tmp;
}


/*
target_cell の「前に」 new_cell が入るように挿入する。挿入後の次のセルのポインタを返す。
*/
cons_t insert(DoublyLL_t ll_t, cons_t target_cell_t, const double x) {
    cons_t new_cell_t = (cons_t)malloc(sizeof(cons));
    if (new_cell_t == NULL) {
        fprintf(stderr, "insert() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    // 追加するセルの設定
    new_cell_t->num = x;
    new_cell_t->previous = target_cell_t->previous;
    new_cell_t->next = target_cell_t;
    // 挿入セルの前のセルの調整, NULL チェックが必要
    if (target_cell_t->previous) target_cell_t->previous->next = new_cell_t;
    // 挿入セルの次のセル (つまり target cell) の調整
    target_cell_t->previous = new_cell_t;
    // head ポインタを変える必要があることもある
    if (target_cell_t == ll_t->head) {
        ll_t->head = new_cell_t;
    }
    // tail ポインタを変える必要があるケースは存在しない
    return target_cell_t;
}


/*
target_cell を削除する。なお、target_cell は必ず指定の LL に存在するものとする。
*/
void delete(DoublyLL_t ll_t, cons_t target_cell_t) {
    if (target_cell_t->previous) target_cell_t->previous->next = target_cell_t->next;
    if (target_cell_t->next) target_cell_t->next->previous = target_cell_t->previous;
    if (ll_t->head == target_cell_t) ll_t->head = target_cell_t->next;
    if (ll_t->tail == target_cell_t) ll_t->tail = target_cell_t->previous;
}


cons head(DoublyLL_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "head() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    return *(ll_t->head);
}


cons tail(DoublyLL_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "tail() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    return *(ll_t->tail);
}


/*
指定値 x が LL 内に存在するか調べ、存在するならそのセルのポインタを、存在しないなら NULL を返す
*/
cons_t find(DoublyLL_t ll_t, double x) {
    if (!is_empty(ll_t)) {
        cons_t current_cell_t = ll_t->head;
        // 要素数 1 の時の扱いがポイント。tail と合致する直前までループし、tail の処理を行うようにすれば空でないとき常にうまくいく
        while (current_cell_t != ll_t->tail) {
            if (current_cell_t->num == x) return current_cell_t;
            current_cell_t = current_cell_t->next;
        }
        if (current_cell_t->num == x) return current_cell_t;
    }
    return NULL;
}