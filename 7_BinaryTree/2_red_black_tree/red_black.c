#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <assert.h>
#include "tree_struct.h"
#include "rotate.h"

#define BLACK true
#define RED false


/** いわゆる平衡二分探索木の一つである赤黒木の実装 (C++ でいう std::map)
 *  
 * 対象は double で表される値を持つ集合であると仮定した。
 * 当然ながら全ての節点は any left-child of x < x <= any right-child of x の二分探索木条件を満たしている。
 * 
 * 今回はそれに加えて以下の 5 つの二色木条件を満たしている。
 * 1. 各節点は RED or BLACK
 * 2. 根は BLACK
 * 3. 全ての葉は BLACK
 * 4. ある節点が RED ならばその子は共に BLACK
 * 5. 各節点について、その節点と子孫の任意の葉を結ぶ単純道は同数の黒節点を含む (自身は含まない)
 * 
 * 
 * これにより
 * - ある道の長さが別の道の長さの 2 倍を超えることはない
 * - 高さ h の上界は 2lg(n+1) 
 * となることがわかる。
 * 
 * 実際に挿入していった結果木は main.c のコメント部分のように構築される。平衡木であることがわかる！ 
 * (cf. 1_binary_search_tree/main.c のコメント部分)
 * 
 */



tree_t make_empty_tree(void) {
    tree_t t_t = (tree_t)malloc(sizeof(tree));
    if (t_t == NULL) {
        fprintf(stderr, "make_empty_tree() in %s: cannot allocate an initial memory to tree\n", __FILE__);
        exit(-1);
    }
    node_t n_t = (node_t)malloc(sizeof(node));
    if (n_t == NULL) {
        fprintf(stderr, "make_empty_tree() in %s: cannot allocate an initial memory to NIL\n", __FILE__);
        exit(-1);
    }
    // 番兵である葉は必ず BLACK
    n_t->color = BLACK;
    // あとは適当
    n_t->value = DBL_MAX; n_t->parent=NULL; n_t->left=NULL; n_t->right=NULL;
    // 番兵の設定
    t_t->NIL = n_t;
    t_t->root = t_t->NIL;
    return t_t;
}


/*
O(n) で巡回 & 出力
中間順木巡回を用いた出力結果は広義単調増加となる
改行はされないので呼び出し側で改行しよう
*/
void inorder_traverse(tree_t t_t, node_t n_t) {
    if (n_t != t_t->NIL) {
        inorder_traverse(t_t, n_t->left);
        printf("%.3f(%s) ", n_t->value, n_t->color?"B":"R");
        inorder_traverse(t_t, n_t->right);
    }
}

void preorder_traverse(tree_t t_t, node_t n_t) {
    if (n_t != t_t->NIL) {
        printf("%.3f(%s) ", n_t->value, n_t->color?"B":"R");
        preorder_traverse(t_t, n_t->left);
        preorder_traverse(t_t, n_t->right);
    }
}

void postorder_traverse(tree_t t_t, node_t n_t) {
    if (n_t != t_t->NIL) {
        postorder_traverse(t_t, n_t->left);
        postorder_traverse(t_t, n_t->right);
        printf("%.3f(%s) ", n_t->value, n_t->color?"B":"R");
    }
}


/*
O(h) で num をある部分木から探索。
発見した場合その節点のポインタを、そうでない場合 NULL を返す。(t_t->NIL ではない)
*/
node_t tree_search(tree_t t_t, node_t n_t, double num) {
    while (n_t != t_t->NIL && n_t->value != num) {
        if (num < n_t->value) {
            n_t = n_t->left;
        } else {
            n_t = n_t->right;
        }
    }
    if (n_t == t_t->NIL) {
        return NULL;
    } else {
        return n_t;
    }
}

/*
O(h) である部分木の最大値、最小値を有する節点を探索し、そのポインタを返す。
*/
node_t tree_min_node(tree_t t_t, node_t n_t) {
    while (n_t->left != t_t->NIL) {
        n_t = n_t->left;
    }
    return n_t;
}

node_t tree_max_node(tree_t t_t, node_t n_t) {
    while (n_t->right != t_t->NIL) {
        n_t = n_t->right;
    }
    return n_t;
}


/*
中間順木巡回で定まる順序において、ある節点の次節点、前節点を O(h) で決定する。
節点が存在する場合はそのポインタを、存在しない場合 NULL を返す。 (t_t->NIL ではない)
*/
node_t successor(tree_t t_t, node_t n_t) {
    if (n_t->right) {
        return tree_min_node(t_t, n_t->right);
    } else {
        while (n_t->parent != t_t->NIL && n_t->parent->left != n_t) {
            n_t = n_t->parent;
        }
        if (n_t->parent == t_t->NIL) {
            return NULL;
        } else {
            return n_t->parent;
        }
    }   
}

node_t predecessor(tree_t t_t, node_t n_t) {
    if (n_t->left) {
        return tree_max_node(t_t, n_t->left);
    } else {
        while (n_t->parent != t_t->NIL && n_t->parent->right != n_t) {
            n_t = n_t->parent;
        }
        if (n_t->parent == t_t->NIL) {
            return NULL;
        } else {
            return n_t->parent;
        }
    }
}



/*
insert_node() で使用する補助関数
n_t に挿入節点 (RED) のポインタを受け取り、適切に二色木条件を回復する。

常にループ開始時点で満たされていない二色木条件は 2, 4 のみ。 ループ終了時点で 4 は満たされている。
根が赤の二色木を緩和二色木というが、この根を黒彩色しても他の二色木条件は壊れず、ただ 2 のみが満たされる。最後に根を黒彩色すれば良い。
*/
void rb_insert_fixup(tree_t t_t, node_t n_t) {
    while (n_t->parent->color == RED) {
        node_t p = n_t->parent;
        assert(p->parent->color == BLACK);
        if (p->left == n_t && p->parent->left == p) {
            right_rotate(t_t, p->parent);
        } else if (p->right == n_t && p->parent->left == p) {
            LR_rotate(t_t, p->parent);
        } else if (p->left == n_t && p->parent->right == p) {
            RL_rotate(t_t, p->parent);
        } else if (p->right == n_t && p->parent->right == p) {
            left_rotate(t_t, p->parent);
        } else {
            fprintf(stderr, "rb_insert_fixup() in %s: unhandled cases?\n", __FILE__);
            exit(-1);
        }
        n_t->color = BLACK;
        n_t = p;
    }
    t_t->root->color = BLACK;
}



/*
O(h) で二分探索木に対しノードを挿入する。ノードの初期色は RED
rb_insert_fixup() を用いて二色木条件を回復する。
*/
void insert_node(tree_t t_t, double num) {
    node_t new_n_t = (node_t)malloc(sizeof(node));
    if (new_n_t == NULL) {
        fprintf(stderr, "insert_node() in %s: cannot allocate a memory to a node\n", __FILE__);
        exit(-1);
    }
    // 挿入節点の初期色は RED
    new_n_t->color = RED;
    new_n_t->value = num;
    new_n_t->left = t_t->NIL;
    new_n_t->right = t_t->NIL;
    node_t n_t = t_t->root;
    if (n_t == t_t->NIL) {
        // 追加節点の親節点の子属性は設定しなくて良い
        // 追加節点の親属性の設定
        new_n_t->parent = t_t->NIL;
        // root を設定してやる
        t_t->root = new_n_t;
    } else {
        // おさまる NIL の位置の親の節点でストップしたい (NIL へ移動してしまうと親を辿れないので)
        while (1) {
            if (num < n_t->value) {
                if (n_t->left != t_t->NIL) n_t = n_t->left; else break;
            } else {
                if (n_t->right != t_t->NIL) n_t = n_t->right; else break;
            }
        }
        // 追加節点の親節点の子属性は設定
        if (num < n_t->value) {
            n_t->left = new_n_t;
        } else {
            n_t->right = new_n_t;
        }
        // 追加節点の親属性の設定
        new_n_t->parent = n_t;
    }
    // postorder_traverse(t_t, t_t->root); //kesu
    // printf("moo\n");
    rb_insert_fixup(t_t, new_n_t);
}



/*
delete_node() で使用する補助関数
u_t の親の子供の位置に v_t 以下の部分木がくるように、v_t 部分木を O(1) で機械的に移し替える。
(u_t の親が v_t の親になるわけではない。u_t 節点はかつての親や子供を参照し続けることに注意。オブジェクトは生き残るのでよしなに属性を書き換えて使用できる -> delete_node())
(不要となった node 構造体の解放処理を呼び出しもとで行う必要がある)
なお、この関数では二分探索木条件が保持されるかどうかなどは考慮しない。
*/
void transplant(tree_t t_t, node_t u_t, node_t v_t) {
    // u_t の親の子属性の設定
    if (u_t->parent == t_t->NIL) {
        t_t->root = v_t;
    } else if (u_t->parent->left == u_t) {
        u_t->parent->left = v_t;
    } else {
        u_t->parent->right = v_t;
    }
    // v_t の親属性の設定 (NIL チェックはしなくても良い)
    v_t->parent = u_t->parent;
}



/*
delte_node() で使用する補助関数
n_t に黒が足りなくなった部分木の根を受け取り、適切に二色木条件を回復する。
*/
void rb_delete_fixup(tree_t t_t, node_t n_t) {
    if (n_t != t_t->root) {
        node_t p = n_t->parent;
        bool original_color_of_p = p->color;
        if (p->left == n_t) {
            // 自身が左の子
            if (p->right->color == RED) {
                // (pattern 1-1) 兄弟が RED
                left_rotate(t_t, p);
                p->color = RED;
                p->parent->color = BLACK;
                rb_delete_fixup(t_t, n_t);    // (pattern 2-1 or 3-1 or 4-1. 4-1 だとしても再帰しないためこの呼び出し一回で終了する)
            } else if (p->right->left->color == RED) {
                // (pattern 2-1) 兄弟が BLACK, その左の子は RED
                RL_rotate(t_t, p);
                p->color = BLACK;
                p->parent->right->color = BLACK;
                p->parent->color = original_color_of_p;
            } else if (p->right->right->color == RED) {
                // (pattern 3-1) 兄弟が BLACK, その右の子は RED
                left_rotate(t_t, p);
                p->color = BLACK;
                p->parent->right->color = BLACK;
                p->parent->color = original_color_of_p;
            } else {
                // (pattern 4-1) 兄弟が BLACK, その両方の子が BLACK
                p->color = BLACK;
                p->right->color = RED;
                if (original_color_of_p == BLACK) {
                    rb_delete_fixup(t_t, p);
                }
            }
        } else {
            // 自身が右の子
            if (p->left->color == RED) {
                right_rotate(t_t, p);
                p->color = RED;
                p->parent->color = BLACK;
                rb_delete_fixup(t_t, n_t);
            } else if (p->left->right->color == RED) {
                LR_rotate(t_t, p);
                p->color = BLACK;
                p->parent->left->color = BLACK;
                p->parent->color = original_color_of_p;
            } else if (p->left->left->color == RED) {
                right_rotate(t_t, p);
                p->color = BLACK;
                p->parent->left->color = BLACK;
                p->parent->color = original_color_of_p;            
            } else {
                p->color = BLACK;
                p->left->color = RED;
                if (original_color_of_p == BLACK) {
                    rb_delete_fixup(t_t, p);
                }
            }
        }
    }
    t_t->root->color = BLACK;
}



/*
O(h) で二分探索木の指定された節点を削除する
なお、指定された節点は必ずこの探索木内に存在すると仮定している。

ポイントは n_t 削除後に n_t がいた位置におさまる節点 x として、
- y ... 黒が足りていない木の根。以前 x がいた場所（両方子供あり） or 以前 n_t がいた場所（子供は高々片方のみ）
- original_color_of_x ... x のもとの色
をメモしておくこと。
*/
void delete_node(tree_t t_t, node_t n_t) {
    node_t y;
    node_t x = n_t;
    bool original_color_of_x = x->color;
    // 子供なし or 右のみ子供
    if (n_t->left == t_t->NIL) {
        y = n_t->right;   // この節点は「transplant の結果」n_t が存在した位置に格納される
        transplant(t_t, n_t, n_t->right);
    // 左のみ子供
    } else if (n_t->right == t_t->NIL) {
        y = n_t->left;    // この節点は「transplant の結果」n_t が存在した位置に格納される
        transplant(t_t, n_t, n_t->left);
    // 両方子供
    // n_t の位置に n_t の次節点を鉢植えし、適切にポインタを調節する
    } else {
        node_t x = tree_min_node(t_t, n_t->right);
        original_color_of_x = x->color;
        y = x->right;   // この節点は 「transplant の結果」以前 x が存在した位置に格納される。
        if (x != n_t->right) {
            transplant(t_t, x, x->right);
            x->right = n_t->right;
            x->right->parent = x;
        } else {
            y->parent = x;    // これやらないと適切に親を辿れなくなる
        }
        transplant(t_t, n_t, x);
        x->left = n_t->left;
        n_t->left->parent = x;
        x->color = n_t->color;
    }
    // n_t 節点のみを回収する。当然再帰的に回収してはならない
    free(n_t);
    // original_color_of_x が黒であった場合、壊れている。二色木条件の回復を行う。
    if (original_color_of_x == BLACK) {
        rb_delete_fixup(t_t, y);
    }
}



/*
double num を long n 個要素にもつ配列を受け取り、O(nlgn) で二分探索木を構築してそのポインタを返す
*/
tree_t build_red_black_tree(double arr[], long n) {
    tree_t t_t = make_empty_tree();
    if (t_t == NULL) {
        fprintf(stderr, "build_BST() in %s: cannot allocate an initial memory to tree\n", __FILE__);
        exit(-1);
    }
    for (long i=0; i<n; i++) {
        insert_node(t_t, arr[i]);
    }
    return t_t;
}
