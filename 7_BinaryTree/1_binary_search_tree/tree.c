#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/** いわゆる二分探索木の実装
 *  
 * 対象は double で表される値を持つ集合であると仮定した。
 * 全ての節点は any left-child of x < x <= any right-child of x の二分探索木条件を満たしている。
 * 
 * 空の二分探索木を構築する make_empty_tree(),
 * 中間順木巡回、先行順木巡回、後行順木巡回を行い要素出力をする inorder_traverse(), preorder_traverse(), postorder_traverse(),
 * 部分木から特定の要素を持つ節点を探索する tree_search(),
 * 部分木から最小値、最大値を持つ節点を探索する tree_min_node(), tree_max_node(),
 * 中間順木巡回で決まる順序において、ある節点の次節点、前節点を決定する successor(), predecessor(),
 * 二分探索木に要素を追加、削除する insert_node(), delete_node()
 * 配列から二分探索木を構築する build_BST(), ランダム二分探索木を構築する build_Randomized_BST()
 * を実装した。
 * 
 * 
 * 巡回の計算量は O(n)。
 * tree_search(), tree_min_node(), tree_max_node(), successor(), predecessor(), insert_node(), delete_node()
 * の計算量は、高さ h として O(h)。
 * 配列からの二分探索木の構築の計算量は O(nlgn)。
 * 
 */


struct vertex {
    double value;
    struct vertex* parent;    // 根の場合 NULL
    struct vertex* left;    // 葉の場合 NULL
    struct vertex* right;    // 葉の場合 NULL
};

typedef struct vertex node, *node_t;


typedef struct {
    node* root;    // 空の場合 NULL
} tree, *tree_t;



tree_t make_empty_tree(void) {
    tree_t t_t = (tree_t)malloc(sizeof(tree));
    if (t_t == NULL) {
        fprintf(stderr, "make_empty_tree() in %s: cannot allocate an initial memory\n", __FILE__);
        exit(-1);
    }
    t_t->root = NULL;
    return t_t;
}

/*
O(n) で巡回 & 出力
中間順木巡回を用いた出力結果は広義単調増加となる
改行はされないので呼び出し側で改行しよう
*/
void inorder_traverse(node_t n_t) {
    if (n_t != NULL) {
        inorder_traverse(n_t->left);
        printf("%.3f ", n_t->value);
        inorder_traverse(n_t->right);
    }
}

void preorder_traverse(node_t n_t) {
    if (n_t != NULL) {
        printf("%.3f ", n_t->value);
        preorder_traverse(n_t->left);
        preorder_traverse(n_t->right);
    }
}

void postorder_traverse(node_t n_t) {
    if (n_t != NULL) {
        postorder_traverse(n_t->left);
        postorder_traverse(n_t->right);
        printf("%.3f ", n_t->value);
    }
}


/*
O(h) で num をある部分木から探索。
発見した場合その節点のポインタを、そうでない場合 NULL を返す。
*/
node_t tree_search(node_t n_t, double num) {
    while (n_t != NULL && n_t->value != num) {
        if (num < n_t->value) {
            n_t = n_t->left;
        } else {
            n_t = n_t->right;
        }
    }
    return n_t;
}

/*
O(h) である部分木の最大値、最小値を有する節点を探索し、そのポインタを返す。
*/
node_t tree_min_node(node_t n_t) {
    while (n_t->left != NULL) {
        n_t = n_t->left;
    }
    return n_t;
}

node_t tree_max_node(node_t n_t) {
    while (n_t->right != NULL) {
        n_t = n_t->right;
    }
    return n_t;
}


/*
中間順木巡回で定まる順序において、ある節点の次節点、前節点を O(h) で決定する。
節点が存在する場合はそのポインタを、存在しない場合 NULL を返す。
*/
node_t successor(node_t n_t) {
    if (n_t->right) {
        return tree_min_node(n_t->right);
    } else {
        while (n_t->parent != NULL && n_t->parent->left != n_t) {
            n_t = n_t->parent;
        }
        return n_t->parent;
    }
}

node_t predecessor(node_t n_t) {
    if (n_t->left) {
        return tree_max_node(n_t->left);
    } else {
        while (n_t->parent != NULL && n_t->parent->right != n_t) {
            n_t = n_t->parent;
        }
        return n_t->parent;
    }
}


/*
O(h) で二分探索木に対しノードを挿入する
*/
void insert_node(tree_t t_t, double num) {
    node_t new_n_t = (node_t)malloc(sizeof(node));
    if (new_n_t == NULL) {
        fprintf(stderr, "insert_node() in %s: cannot allocate a memory to a node\n", __FILE__);
        exit(-1);
    }
    new_n_t->value = num;
    new_n_t->left = NULL;
    new_n_t->right = NULL;
    node_t n_t = t_t->root;
    if (n_t == NULL) {
        // 追加節点の親節点の子属性は設定しなくて良い
        // 追加節点の親属性の設定
        new_n_t->parent = NULL;
        // root をしてやる
        t_t->root = new_n_t;
    } else {
        // おさまる NULL の位置の親の節点でストップしたい (NULL へ移動してしまうと親を辿れないので)
        while (1) {
            if (num < n_t->value) {
                if (n_t->left) n_t = n_t->left; else break;
            } else {
                if (n_t->right) n_t = n_t->right; else break;
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
    if (u_t->parent == NULL) {
        t_t->root = v_t;
    } else if (u_t->parent->left == u_t) {
        u_t->parent->left = v_t;
    } else {
        u_t->parent->right = v_t;
    }
    // v_t の親属性の設定
    if (v_t != NULL) v_t->parent = u_t->parent;
}


/*
O(h) で二分探索木の指定された節点を削除する
なお、指定された節点は必ずこの探索木内に存在すると仮定している。
*/
void delete_node(tree_t t_t, node_t n_t) {
    // 子供なし or 右のみ子供
    if (n_t->left == NULL) {
        transplant(t_t, n_t, n_t->right);
    // 左のみ子供
    } else if (n_t->right == NULL) {
        transplant(t_t, n_t, n_t->left);
    // 両方子供
    // n_t の位置に n_t の次節点を鉢植えし、適切にポインタを調節する
    } else {
        node_t x = tree_min_node(n_t->right);
        if (x != n_t->right) {
            transplant(t_t, x, x->right);
            x->right = n_t->right;
            n_t->right->parent = x;
        }
        transplant(t_t, n_t, x);
        x->left = n_t->left;
        n_t->left->parent = x;
    }
    // n_t 節点のみを回収する。当然再帰的に回収してはならない
    free(n_t);
}



/*
double num を long n 個要素にもつ配列を受け取り、O(nlgn) で二分探索木を構築してそのポインタを返す
*/
tree_t build_BST(double arr[], long n) {
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


void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


void shuffle(double arr[], long n) {
    srand(time(NULL));
    for (long i=0; i<n; i++) {
        // [i] と [i...n-1] を交換する (i+1...n-1 はランダム置換にならないぞ)
        // n-1-i+1 = n-i
        // (double)(RAND_MAX+1) で割り算をしようとすると int の計算ところでオーバーフローするのでダメ (一敗)
        long x = i + (long)(rand() * (n - i) / (RAND_MAX+1.0));
        swap(arr + i, arr + x);
    }
}



/*
double num を long n 個要素にもつ配列を受け取り、O(nlgn) で二分探索木を構築してそのポインタを返す
シャッフルをかけてから木の構築を行うことで、どのような敵対的入力に対しても二分探索木の期待高さ h = O(lgn) にできる。
*/
tree_t build_Randomized_BST(double arr[], long n) {
    double* tmp = (double*)malloc(sizeof(double) * n);
    if (tmp == NULL) {
        fprintf(stderr, "build_Randomized_BST() in %s: cannot allocate a memory to a copy of array\n", __FILE__);
        exit(-1);
    }
    for (long i=0; i<n; i++) {
        tmp[i] = arr[i];
    }
    shuffle(tmp, n);
    tree_t t_t = build_BST(tmp, n);
    free(tmp);
    return t_t;
}