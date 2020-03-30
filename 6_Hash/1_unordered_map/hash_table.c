#include <stdio.h>
#include <stdlib.h>
#include "hash_func.h"
#include "struct_for_hash.h"
#include "doublyLL_record.h"


/** いわゆる hashtable, dictionary, unordered map の実装
 * 
 * チェイン法とオープアドレス法で実装
 * 対象はキーとして文字列をもち、それに対応する形で double で表現される値を持つと仮定した。
 * 値の挿入、検索の時のアルゴリズムをいじればいわゆる chainmap, unordered multimap になる。
 * 
 * 値の検索、挿入、削除の計算量 O(1)
 */



/* 文字列を受け取り、ハッシュ値を計算して返す */
int hash_key(char* key) {
    return devision_hash(ascii_to_int_base_128(key));
}


/* ======== chain method ======== */
/* ============================== */

chained_hashtab_t make_chained_hash_table(void) {
    chained_hashtab_t h_t = (chained_hashtab_t)malloc(sizeof(chained_hashtab));
    if (h_t == NULL) {
        fprintf(stderr, "make_hash_table() in %s: cannot allocate initial memory\n", __FILE__);
        exit(-1);
    }
    h_t->size = 1024;
    for (int i=0; i<h_t->size; i++) {
        (h_t->arr)[i] = make_empty_doubly_ll();
    }
    return h_t;
}


void print_chained_hash(chained_hashtab_t h_t) {
    printf("hashtable: {\n");
    for (int i=0; i<1024; i++) {
        if ((h_t->arr)[i]->head != NULL) print_doubly_ll((h_t->arr)[i]);
    }
    printf("}\n");
}


/*
チェインハッシュにレコードを挿入する
レコードのキーでもってハッシュ値を計算し、その位置の双方向連結リストにレコード全体を収納しておく。
すでに存在する場合は追加ではなく上書きを行う。(追加を行うようにしたら unordered_multiple_map になる)
*/
void chained_hash_insert(chained_hashtab_t h_t, record_t x) {
    char* name = x->key;
    DoublyLL_t ll_t = (h_t->arr)[hash_key(name)];
    if (!find_rec_by_key(ll_t, name)) {
        push_front(ll_t, x);
    } else {
        find_rec_by_key(ll_t, name)->rec_t = x;
    }
}


/*
キーの文字列でもってチェインハッシュを検索する
レコードのキーでもってハッシュ値を計算し、その双方向連結リストを探索する。
見つからなかった場合はキーエラーということで異常終了し、見つかった場合はそのキーと対応するバリューを返す。
*/
double chained_hash_search(chained_hashtab_t h_t, char* name) {
    DoublyLL_t ll_t = (h_t->arr)[hash_key(name)];
    cons_t c_t = find_rec_by_key(ll_t, name);    // 見つからなかったときは NULL
    if (c_t == NULL) {
        fprintf(stderr, "chained_hash_search() in %s: cannot find record that has %s as a key\n", __FILE__, name);
        exit(-1);
    }
    return c_t->rec_t->value;
}


/*
ある文字列と同一のキーを持つチェインハッシュの要素を削除する
レコードのキーでもってハッシュ値を計算し、その双方向連結リストを探索する。
見つからなかった場合は何もせず、見つかった場合はそのセルを削除する。
*/
void chained_hash_delete(chained_hashtab_t h_t, char* name) {
    DoublyLL_t ll_t = (h_t->arr)[hash_key(name)];
    cons_t c_t = find_rec_by_key(ll_t, name);
    if (c_t != NULL) {
        delete_cons(ll_t, c_t);
    }
}
/* ======== chain method ======== */
/* ============================== */




/* ======== open addressing method ======== */
/* ======================================== */
// to be continued!
