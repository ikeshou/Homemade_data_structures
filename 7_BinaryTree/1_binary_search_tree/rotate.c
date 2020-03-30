#include <stdio.h>
#include "tree.h"


/*
木の回転操作をまとめたもの
単回転 ... left_rotate(), right_rotate()
*/



/*
left_rotate ... n_t 自身を、n_t の右の子を回転中心として左回転させる。
right_rotate ...                左の子              右回転
二分探索木条件を満たすよう適切に子供を付け替える。
なお回転中心である left_rotate の際の右の子、right_rotate の際の左の子は t_t->NIL ではないとする。

アルファベットを節点、<ギリシャ文字>を木とする。節点 y 中心の回転は
        
        y          rRot           x
    x       <γ>    ->       <α>         y
 <α> <β>           <-                <β>  <γ>   
                   lRot

のようになる。                
*/
void left_rotate(tree_t t_t, node_t n_t) {
    node_t pivot = n_t->right;
    if (n_t->parent != NULL) {
        // 自身の親の設定
        if (n_t->parent->left == n_t) {
            n_t->parent->left = pivot;
        } else {
            n_t->parent->right = pivot;
        }
    } else {
        // root の設定
        t_t->root = pivot;
    }
    // 回転中心の子の設定 (β)
    if (pivot->left) pivot->left->parent = n_t;
    // 回転中心の設定 (y)、自身の設定 (x) 交互に (ポインタが上書きされないように注意)
    pivot->parent = n_t->parent;
    n_t->right = pivot->left;
    pivot->left = n_t;    
    n_t->parent = pivot;
}


void right_rotate(tree_t t_t, node_t n_t) {
    node_t pivot = n_t->left;
    if (n_t->parent != NULL) {
        // 自身の親の設定
        if (n_t->parent->left == n_t) {
            n_t->parent->left = pivot;
        } else {
            n_t->parent->right = pivot;
        }
    } else {
        // root の設定
        t_t->root = pivot;
    }
    // 回転中心の子の設定 (β)
    if (pivot->right) pivot->right->parent = n_t;
    // 回転中心の設定 (y)、自身の設定 (x) 交互に (ポインタが上書きされないように注意)
    pivot->parent = n_t->parent;
    n_t->left = pivot->right;
    pivot->right = n_t;    
    n_t->parent = pivot;
}