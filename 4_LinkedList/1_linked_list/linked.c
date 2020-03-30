#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/** 単方向連結リストの実装 
 * 
 * double で表される値と次の要素へのポインタを持つセルの集合を仮定し実装。
 * (もちろん double の位置にまた別の構造体が入るような使い方がメインだろう)
 * (ポインタではなく、配列による表現も可能。次の要素を格納しているインデックスさえ分かればアドレスが定まるので)
 * 
 * 単方向連結リスト作成のための make_empty_linked_list(),
 * 値の追加削除のための push(), pop(),
 * 値の検索のための find(),
 * 状態を調べるための head(), is_empty(),
 * 単方向連結リストの出力のための print_linked_list()
 * を実装した。
 * なお、head ポインタは連結リストの先頭のセル (= 最後に追加されたセル) を常に指している。
 * もちろん連結リストの先頭への値の追加 or 削除の計算量は O(1)、要素の検索は O(n)
 * 
 * また、この時点で連結リストを用いた stack の実装が終わっていることもわかる。
 * 
 * 
 * (メモ：しっかりメモリの片付けをする場合、 recursive_free() のような関数を書いて作成したセルの占有するメモリを再帰的に解放していく必要があるだろう。)
 */



struct cell {
    double num;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;    // 連結リストの先頭のセル (= 最後に追加されたセル) を指すポインタ。空の場合は NULL
} LinkedList, *LinkedList_t;



LinkedList_t make_empty_linked_list(void) {
    LinkedList_t ll_t = (LinkedList_t)malloc(sizeof(LinkedList));
    if (ll_t == NULL) {
        fprintf(stderr, "make_empty_ll() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    ll_t->head = NULL;
    return ll_t;
}


bool is_empty(LinkedList_t ll_t) {
    return ll_t->head == NULL;
}


void print_linked_list(LinkedList_t ll_t) {
    printf("LinkedList: ");
    cons_t current_cell_t = ll_t->head;
    while (current_cell_t != NULL) {
        printf("[%.3f(@%p), next:%p] ", current_cell_t->num, current_cell_t, current_cell_t->next);
        current_cell_t = current_cell_t->next;
    }
    printf("\n");
}


void push(LinkedList_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    // 挿入セルの設定
    c_t->num = x;
    c_t->next = ll_t->head;
    // 現在の head ポインタが挿入セルを指すようにする
    ll_t->head = c_t;
}

cons pop(LinkedList_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "pop() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    cons_t tmp = ll_t->head;
    // 現在の head ポインタが削除セルの次のセルを指すようにする
    ll_t->head = ll_t->head->next;
    return *tmp;
}


cons head(LinkedList_t ll_t) {
    if (is_empty(ll_t)) {
        fprintf(stderr, "head() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    return *(ll_t->head);
}


/*
指定値 x が LL 内に存在するか調べ、存在するならそのセルのポインタを、存在しないなら NULL を返す
*/
cons_t find(LinkedList_t ll_t, double x) {
    cons_t current_cell_t = ll_t->head;
    while (current_cell_t != NULL) {
        if (current_cell_t->num == x) return current_cell_t;
        current_cell_t = current_cell_t->next;
    }
    return NULL;
}