#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** 双方向循環連結リストの実装
 *  
 * 双方向かつ循環であることで head ポインタだけを記憶すれば末尾に O(1) で容易にアクセスできるようになる。
 * 双方向かつ循環であることで rotate(), reverse_rotate() が共に O(1) で行えるようになる。
 * 先頭 or 末尾への値の追加 or 削除が O(1) で行える。
 * 指定したセルの前や後ろへの挿入、指定したセルの削除が O(1) で行える。
 * 
 * 双方向循環連結リストを用いたいわゆる deque の実装が完了していることがわかる。
 * デックというとリングバッファなどの動的配列を用いた実装の方が主流な気がするけれど。
 * (指定箇所への挿入が O(n) になる代わりにランダムアクセス O(1) が許される)
 */



struct cell {
    double num;
    struct cell* previous;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;    // 連結リストの先頭のセル (= 最後に追加されたセル) を指すポインタ。空の場合は NULL
} DoublyLL, *DoublyLL_t;



DoublyLL_t make_empty_doubly_ll(void) {
    DoublyLL_t ll_t = (DoublyLL_t)malloc(sizeof(DoublyLL));
    if (ll_t == NULL) {
        fprintf(stderr, "make_empty_doubly_ll() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    ll_t->head = NULL;
    return ll_t;
}


bool is_empty(DoublyLL_t ll_t) {
    return ll_t->head == NULL;
}


void print_doubly_ll(DoublyLL_t ll_t) {
    printf("DoublyLL: ");
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


void rotate(DoublyLL_t ll_t) {
    if (ll_t->head) ll_t->head = ll_t->head->next;
}

void reverse_rotate(DoublyLL_t ll_t) {
    if (ll_t->head) ll_t->head = ll_t->head->previous;
}


void push_front(DoublyLL_t ll_t, const double x) {
    cons_t c_t = (cons_t)malloc(sizeof(cons));
    if (c_t == NULL) {
        fprintf(stderr, "push_front() in %s: cannot allocate a memory\n", __FILE__);
        exit(-1);
    }
    if (is_empty(ll_t)) {
        c_t->num = x;
        c_t->previous = c_t;
        c_t->next = c_t;
        ll_t->head = c_t;
    } else {
        // 追加するセルの設定
        c_t->num = x;
        c_t->previous = ll_t->head->previous;
        c_t->next = ll_t->head;
        // 挿入セルの前のセルの調整。こちらを次の処理より先にやらないと (正しく辿るためには) 無駄に複雑になるので注意
        ll_t->head->previous->next = c_t;    
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
    if (ll_t->head == ll_t->head->next) {
        ll_t->head = NULL;
    // 要素数 2 以上の時
    } else {
        // 削除セルの次のセルの調整
        ll_t->head->next->previous = ll_t->head->previous;
        // 削除セルの前のセルの調整
        ll_t->head->previous->next = ll_t->head->next;
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
        ll_t->head = c_t;
        c_t->num = x;
        c_t->previous = c_t;
        c_t->next = c_t;
    } else {
        // 追加するセルの設定
        c_t->num = x;
        c_t->previous = ll_t->head->previous;
        c_t->next = ll_t->head;
        // 挿入セルの前のセルの調整。こちらを次の処理より先にやらないと (正しく辿るためには) 無駄に複雑になるので注意
        ll_t->head->previous->next = c_t;        
        // 挿入セルの次のセルの調整
        ll_t->head->previous = c_t;
        // head ポインタは変わらず
    }
}


cons pop_back(DoublyLL_t ll_t) {
    // 要素数 0 の時はエラー
    if (is_empty(ll_t)) {
        fprintf(stderr, "pop_back() in %s: linked list is empty\n", __FILE__);
        exit(-1);
    }
    cons_t tmp = ll_t->head->previous;
    // 要素数 1 の時
    if (ll_t->head == ll_t->head->next) {
        ll_t->head = NULL;
    // 要素数 2 以上の時
    } else {
        // 削除セルの前のセルの調整。こちらを次の処理より先にやらないと (正しく辿るためには) 無駄に複雑になるので注意
        ll_t->head->previous->previous->next = ll_t->head;        
        // 削除セルの次のセルの調整
        ll_t->head->previous = ll_t->head->previous->previous;
        // head ポインタは変わらず
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
    // 挿入セルの前のセルの調整
    target_cell_t->previous->next = new_cell_t;
    // 挿入セルの次のセルの調整
    target_cell_t->previous = new_cell_t;
    // head ポインタを変える必要があることもある
    if (target_cell_t == ll_t->head) {
        ll_t->head = new_cell_t;
    }
    return target_cell_t;
}


/*
target_cell を削除する。なお、target_cell は必ず指定の LL に存在するものとする。
*/
void delete(DoublyLL_t ll_t, cons_t target_cell_t) {
    // 要素数 1 の時
    if (ll_t->head == ll_t->head->previous) {
        ll_t->head = NULL;
    } else {
        // 削除セルの前のセルの調整
        target_cell_t->previous->next = target_cell_t->next;
        // 削除セルの次のセルの調整
        target_cell_t->next->previous = target_cell_t->previous;
        // head ポインタを変える必要があることもある
        if (ll_t->head == target_cell_t) {
            ll_t->head = target_cell_t->next;
        }
    }
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
    return *(ll_t->head->previous);
}


/*
指定値 x が LL 内に存在するか調べ、存在するならそのセルのポインタを、存在しないなら NULL を返す
*/
cons_t find(DoublyLL_t ll_t, double x) {
    if (!is_empty(ll_t)) {
        cons_t current_cell_t = ll_t->head;
        while (current_cell_t != ll_t->head->previous) {
            if (current_cell_t->num == x) return current_cell_t;
            current_cell_t = current_cell_t->next;
        }
        if (current_cell_t->num == x) return current_cell_t;
    }
    return NULL;
}
