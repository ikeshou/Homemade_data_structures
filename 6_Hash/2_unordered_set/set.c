#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_func.h"
#include "struct_for_set.h"
#include "doubly.h"


/** いわゆる unordered set の実装
 * 
 * 対象は double で表現される値を持つ集合であると仮定した。
 * 今回 chained method で実装されたハッシュテーブルの実装を再利用している。
 * キーとバリューが一致したハッシュテーブルはすなわちセットとなるので実装はハッシュテーブルができた段階でほとんど完了している。
 * 因みに、値の挿入、検索の時のアルゴリズムをいじればいわゆる bag, counter, unordered multiset になる。
 * 
 * 値の検索、挿入、削除の計算量 O(1)
 */



/* 
double num を受け取り、ハッシュ値を計算して返す
*/
int hash_key(double num) {
    return multiplication_hash((float)num);   // 浮動小数点数を扱うし乗算法の方で
}


/* ======== chain method ======== */
/* ============================== */

chained_hashtab_t make_set(void) {
    chained_hashtab_t h_t = (chained_hashtab_t)malloc(sizeof(chained_hashtab));
    if (h_t == NULL) {
        fprintf(stderr, "make_set() in %s: cannot allocate initial memory\n", __FILE__);
        exit(-1);
    }
    h_t->size = 1024;
    for (int i=0; i<h_t->size; i++) {
        (h_t->arr)[i] = make_empty_doubly_ll();
    }
    return h_t;
}


void print_set(chained_hashtab_t h_t) {
    printf("set: { ");
    for (int i=0; i<1024; i++) {
        if ((h_t->arr)[i]->head != NULL) print_doubly_ll((h_t->arr)[i]);
    }
    printf("}\n");
}


/*
チェインハッシュに double num を挿入する
レコードのキーでもってハッシュ値を計算し、その位置の双方向連結リストにレコード全体を収納しておく。
すでに存在する場合は追加せず何もしない。(追加を行うようにしたら unordered_multiple_map になる)
*/
void set_insert(chained_hashtab_t h_t, double x) {
    DoublyLL_t ll_t = (h_t->arr)[hash_key(x)];
    if (!find(ll_t, x)) push_front(ll_t, x);
}


/*
double num でもってチェインハッシュを検索する
レコードのキーでもってハッシュ値を計算し、その双方向連結リストを探索する。
見つからなかった場合は false、見つかった場合は true を返す。
*/
bool set_search(chained_hashtab_t h_t, double x) {
    DoublyLL_t ll_t = (h_t->arr)[hash_key(x)];
    cons_t c_t = find(ll_t, x);    // 見つからなかったときは NULL
    return (c_t != NULL);
}


/*
ある double num なる集合の要素を削除する
レコードのキーでもってハッシュ値を計算し、その双方向連結リストを探索する。
見つからなかった場合は何もせず、見つかった場合はそのセルを削除する。
*/
void set_delete(chained_hashtab_t h_t, double x) {
    DoublyLL_t ll_t = (h_t->arr)[hash_key(x)];
    cons_t c_t = find(ll_t, x);
    if (c_t != NULL) delete(ll_t, c_t);
}
/* ======== chain method ======== */
/* ============================== */




/* ======== open addressing method ======== */
/* ======================================== */
// to be continued!
