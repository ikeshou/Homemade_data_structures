#include <stdio.h>
#include <assert.h>
#include "tree_struct.h"


/*
木の回転操作をまとめたもの
単回転 ... left_rotate(), right_rotate()
重回転 ... LR_rotate(), RL_rotate()
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
    // NIL には適当なポインタとかが入ったりするので assertion check しないとバグったときに面倒
    assert(n_t != t_t->NIL);
    assert(n_t->right != t_t->NIL);
    node_t pivot = n_t->right;
    if (n_t->parent != t_t->NIL) {
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
    // NIL には適当なポインタとかが入ったりするので assertion check しないとバグったときに面倒
    assert(n_t != t_t->NIL);
    assert(n_t->left != t_t->NIL);
    node_t pivot = n_t->left;
    if (n_t->parent != t_t->NIL) {
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



/*
LR_rotate ... 自身の左の子において left_rotate を行い、そのあと自身に right_rotate を行う。なお、左の子、左の子の右の子は NIL でないものとする。
RL_rotate ...      右           right_rotate                    left_rotate             右の子、右のこの左の子

以下の節点 u に対し LR_rotate() を施すと
            u                                      w 
    v              <t4>         LR          v             u
<t1>   w                        ->      <t1>  <t2>    <t3> <t4>
    <t2><t3>
となる。

以下の節点 u に対し RL_rotate() を施すと
            u                                      w
  <t1>              v           RL          u             v
                w      <t4>     ->     <t1>  <t2>     <t3> <t4>
             <t2><t3>
となる。
*/
void LR_rotate(tree_t t_t, node_t n_t) {
    left_rotate(t_t, n_t->left);
    right_rotate(t_t, n_t);
}


void RL_rotate(tree_t t_t, node_t n_t) {
    right_rotate(t_t, n_t->right);
    left_rotate(t_t, n_t);
}
