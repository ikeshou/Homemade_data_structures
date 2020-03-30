#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** リングバッファを用いた deque の実装
 * 
 * 対象は double num を long n 個要素にもつ配列と仮定。
 * 
 * 空のデック作成を行う make_deque(),
 * 先頭 or 末尾に対する値の追加 or 削除を行う push_front(), pop_front(), push_back(), pop_back(),
 * 先頭 or 末尾の値 or ポインタの取得を行う front(), back(), begin(), end(),
 * ランダムアクセスを行う at(),
 * 内部情報の取得を行う capacity(), size(), is_empty(),
 * デックやバッファの出力を行う print_deque(), traverse_deque()
 * の実装を行った。
 * 
 * 双方向連結リストを用いたデックの実装同様、先頭および末尾への操作が O(1) で行える。
 * こちらは挿入が O(n) かかるため実装されていない代わりに、O(1) でのランダムアクセスがサポートされている。
 * もちろんこれによりリングバッファを用いた stack, queue の実装が完了している。
 * 
 * リングバッファの拡張の際のコピー手続きや、古いメモリ領域の解放手続きを忘れがちなので注意！
 */



typedef struct {
    long capacity; // 拡張なく入れることのできる要素数
    long size; // 現在の要素数
    long head_ind;    // 先頭の要素を示すインデックス
    long tail_ind;    // 末尾の要素を示すインデックス
    double* arr;    // リングバッファとして使用する。arr[0] は必ずしも先頭の要素を表さない。
} deque, *deque_t;


deque_t make_deque(void) {
    // ここで返された deque について。このポインタを通して free するだけではなく、arr メンバ領域も free する必要があることに注意
    deque_t deq_t = (deque_t)malloc(sizeof(deque));
    if (deq_t == NULL) {
        fprintf(stderr, "make_deque() in %s: cannot allocate a memory.\n", __FILE__);
        exit(-1);
    }
    deq_t->capacity = 4;    // 今回初期サイズは 4 にした
    deq_t->size = 0;
    deq_t->head_ind = -1;    // 要素追加時に正しく初期化される
    deq_t->tail_ind = -1;    // 要素追加時に正しく初期化される
    deq_t->arr = (double*)calloc(4, sizeof(double));
    if (deq_t->arr == NULL) {
        fprintf(stderr, "make_deque() in %s: cannot allocate an intial memory\n", __FILE__);
        exit(-1);
    } 
    return deq_t;
}


long capacity(deque_t deq_t) {
    return deq_t->capacity;
}

long size(deque_t deq_t) {
    return deq_t->size;
}

bool is_empty(deque_t deq_t) {
    return (bool)(deq_t->size == 0);
}

/* リングバッファの内容を確認する用。空白部分も含めて確保されたメモリの先頭部分から出力される */
void print_deque(deque_t deq_t) {
    long start = deq_t->head_ind;
    long end = deq_t->tail_ind;
    printf("capacity: %ld, number of element: %ld, start: %ld, end: %ld ", capacity(deq_t), size(deq_t), start, end);
    printf("buffer: ");
    for (long i=0; i<deq_t->capacity; i++) {
        printf("%.3f ", (deq_t->arr)[i]);
    }
    printf("\n");
}

/* リストの中身を確認する用。先頭から末尾まで順に出力される */
void traverse_deque(deque_t deq_t) {
    long start = deq_t->head_ind;
    long end = deq_t->tail_ind;
    printf("deque contents: ");
    long i = start;
    if (!is_empty(deq_t)) {
        while (i != end) {
            printf("%.3f ", (deq_t->arr)[i]);
            i = (i+1)%(deq_t->capacity);
        }
        printf("%.3f ", (deq_t->arr)[i]);    // end と一致したらそれを出力しておしまい
    }
    printf("\n");
}


/* 
push_back(), pop_back(), push_front(), pop_front() で使用する補助関数
next_tail_ind(), previous_tail_ind(), next_head_ind(), previous_head_ind()
いずれもまだリングバッファに空きが存在するという仮定の上で、それぞれ指定された位置を指し示すインデックスを計算している
*/
long next_tail_ind(deque_t deq_t) {
    return ((deq_t->tail_ind)+1)%(deq_t->capacity);
}

long previous_tail_ind(deque_t deq_t) {
    return ((deq_t->tail_ind)-1+deq_t->capacity)%(deq_t->capacity);
}

long next_head_ind(deque_t deq_t) {
    return ((deq_t->head_ind)+1)%(deq_t->capacity);
}

long previous_head_ind(deque_t deq_t) {
    return ((deq_t->head_ind)-1+deq_t->capacity)%(deq_t->capacity);
}


void push_back(deque_t deq_t, const double num) {
    if (is_empty(deq_t)) {
        deq_t->size++;
        deq_t->head_ind = 0;
        deq_t->tail_ind = 0;
        (deq_t->arr)[0] = num;
    } else {
        if (deq_t->capacity == deq_t->size) {
            // リングバッファなので realloc のコピーに任せてそのままもとのバッファの内容を使い回すことはできない。
            // 必ず新しい領域にメモリを確保し、手動でコピーを行う。
            double* ptr = (double*)calloc((deq_t->capacity * 2), sizeof(double));
            if (ptr == NULL) {
                fprintf(stderr, "push_back() in %s: cannot allocate an extra memory\n", __FILE__);
                exit(-1);
            } else {
                // copy!
                for (long i=0; i<deq_t->size; i++) {
                    ptr[i] = (deq_t->arr)[(deq_t->head_ind+i)%(deq_t->capacity)];
                }
                free(deq_t->arr);    // これを忘れるとリーク
                deq_t->arr = ptr;
                deq_t->capacity *= 2;
                deq_t->head_ind = 0;
                deq_t->tail_ind = deq_t->size - 1;
            }
        }
        deq_t->size++;
        deq_t->tail_ind = next_tail_ind(deq_t);
        (deq_t->arr)[deq_t->tail_ind] = num;
    }
}


double pop_back(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "pop_back() in %s: cannot pop from an empty deque\n", __FILE__);
        exit(-1);
    }
    double popped = (deq_t->arr)[deq_t->tail_ind];
    deq_t->size--;
    deq_t->tail_ind = previous_tail_ind(deq_t);
    return popped;
}


void push_front(deque_t deq_t, const double num) {
    if (is_empty(deq_t)) {
        deq_t->size++;
        deq_t->head_ind = 0;
        deq_t->tail_ind = 0;
        (deq_t->arr)[0] = num;
    } else {
        if (deq_t->capacity == deq_t->size) {
            // リングバッファなので realloc のコピーに任せてそのままもとのバッファの内容を使い回すことはできない。
            // 必ず新しい領域にメモリを確保し、手動でコピーを行う。
            double* ptr = (double*)calloc((deq_t->capacity * 2), sizeof(double));
            if (ptr == NULL) {
                fprintf(stderr, "push_back() in %s: cannot allocate an extra memory\n", __FILE__);
                exit(-1);
            } else {
                // copy!
                for (long i=0; i<deq_t->size; i++) {
                    ptr[i] = (deq_t->arr)[(deq_t->head_ind+i)%(deq_t->capacity)];
                }
                free(deq_t->arr);    // これを忘れるとリーク
                deq_t->arr = ptr;
                deq_t->capacity *= 2;
                deq_t->head_ind = 0;
                deq_t->tail_ind = deq_t->size - 1;                
            }
        }
        deq_t->size++;
        deq_t->head_ind = previous_head_ind(deq_t);
        (deq_t->arr)[deq_t->head_ind] = num;
    }
}


double pop_front(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "pop_back() in %s: cannot pop from an empty deque\n", __FILE__);
        exit(-1);
    }
    double popped = (deq_t->arr)[deq_t->head_ind];
    deq_t->size--;
    deq_t->head_ind = next_head_ind(deq_t);
    return popped;
}



/* cpp の deque だったら参照が返るけど今回は値を返している */
double at(deque_t deq_t, const long ind) {
    if (ind > deq_t->size - 1) {
        fprintf(stderr, "at() in %s: out of range\n", __FILE__);
        exit(-1);
    }
    return (deq_t->arr)[(deq_t->head_ind + ind)%(deq_t->capacity)];
}

double front(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "front() in %s: deque is empty\n", __FILE__);
        exit(-1);
    }
    return (deq_t->arr)[deq_t->head_ind];
}

double back(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "front() in %s: deque is empty\n", __FILE__);
        exit(-1);
    } 
    return (deq_t->arr)[deq_t->tail_ind];
}


/* cpp の deque だったらイテレータが返るけど今回はポインタを返している */
double* begin(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "begin() in %s: deque is empty\n", __FILE__);
        exit(-1);
    }
    return deq_t->arr + deq_t->head_ind;
}

double* end(deque_t deq_t) {
    if (is_empty(deq_t)) {
        fprintf(stderr, "end() in %s: deque is empty\n", __FILE__);
        exit(-1);
    }
    return deq_t->arr + deq_t->tail_ind;
}