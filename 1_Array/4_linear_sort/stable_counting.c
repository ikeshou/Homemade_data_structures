#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** いわゆる計数ソートの実装
 * 
 * counting sort, radix sort を実装した。
 * 安定性の確認のため、counting sort の対象としては 文字と数値を属性としてもつ構造体を long n 個要素にもつ配列、long num を long n 個要素にもつ (値の範囲は long k) 配列を仮定した。
 * radix sort の対象としては 10 進数で long d 桁の数字を long n 個要素にもつ配列を仮定した。
 * counting sort の計算量は O(k+n), radix sort の計算量は O(d(k+n))
 */



typedef struct {
    char mark;    // H, S, D, C
    long number;    // 1 ~ 13
} Card;


/*
値の範囲 0-k, 要素数 n として O(k+n) で安定ソートを行う
今回対象とする要素は上記構造体で、その number に対し計数ソートをかける
*/
#define TRUMP 13
void counting_sort_trump(Card arr[], long n) {
    // (0), 1, 2, ..., 13 用の箱を用意
    long bin[TRUMP+1] = {0};
    // bin[i] は i と同じ数の出現数を示す
    for (long i=0; i<n; i++) {
        bin[arr[i].number]++;
    }
    // bin[i] は i 以下の数の出現数を示す
    for (long j=1; j<TRUMP+1; j++) {
        bin[j] += bin[j-1];
    }
    // arr の各要素について末尾から収まるべき位置に収納していく
    Card* tmp = (Card*)malloc(sizeof (Card) * n);
    for (long i=0; i<n; i++) {
        tmp[i] = arr[i];
    }
    for (long i=n-1; i>=0; i--) {
        arr[bin[tmp[i].number] - 1] = tmp[i];    // 自分含め bin[tmp[i].number] 個前に存在する。つまり index でいうとそれ -1 した位置に収まる。
        bin[tmp[i].number]--;
    }
    free(tmp);
}


void print_trump_array(Card arr[], long n) {
    for (long i=0; i<n; i++) {
        printf("%c%ld", arr[i].mark, arr[i].number);
        printf(" ");
    }
    printf("\n");
}


/*
値の範囲 0-k, 要素数 n として O(k+n) で安定ソートを行う
long を要素として持つ array に対し計数ソートをかける
*/
void counting_sort(long arr[], long n, long k) {
    long* bin = (long*)calloc(k+1, sizeof (long));
    for (long i=0; i<n; i++) bin[arr[i]]++;
    for (long j=1; j<k+1; j++) bin[j] += bin[j-1];
    long* tmp = (long*)malloc(sizeof (long) * n);
    for (long i=0; i<n; i++) {
        tmp[i] = arr[i];
    }
    for (long i=n-1; i>=0; i--) {
        arr[bin[tmp[i]] - 1] = tmp[i];
        bin[tmp[i]]--;
    }
    free(tmp);
}

void print_long_array(long arr[], long n) {
    for (long i=0; i<n; i++) {
        printf("%ld", arr[i]);
        printf(" ");
    }
    printf("\n");
}


/*
ltos(1234)
// => {'1', '2', '3', '4', '\0'} なる配列がヒープ領域に作成されそのポインタが返る
*/
char* ltos(long num, long d) {
    char* str = (char*)malloc(sizeof (char) * (d+1));
    for (long i=0; i<d; i++) {
        str[i] = '0' + ((num / (long)(pow(10, d-1-i))) % 10);
    }
    str[d] = '\0';
    return str;
}


void nested_free(char **pp, long n) {
    if (pp != NULL) {
        for (long i=0; i<n; i++) {
            if (pp[i] != NULL) {
                free(pp[i]);
                pp[i] = NULL;
            }
        }
        free(pp);
        *pp = NULL;
    }
}



void print_char_array(char* arr[], long n) {
    for (long i=0; i<n; i++) {
        long j = 0;
        while (arr[i][j]) {
            printf("%c", arr[i][j]);
            j++;
        }
        printf(" ");
    }
    printf("\n");
}


/*
d 桁の十進数を要素として持つ array に対し基数ソートをかける
*/
# define DIGIT 10
void radix_sort(long arr[], long n, long d) {
    // 各桁に注目しやすくするために文字列化
    char** converted = (char**)malloc(sizeof (char*) * n);
    for (long i=0; i<n; i++) converted[i] = ltos(arr[i], d);
    
    // 下の位から各桁に対し計数ソートをかけていく
    for (long j=d-1; j>=0; j--) {
        // (0), 1, 2, ..., 9 用の箱を用意
        long bin[DIGIT] = {0};
        // bin[i] は i と同じ数の出現数を示す
        for (long i=0; i<n; i++) {
            bin[(converted[i][j]) - '0']++;    // char to int
        }
        // bin[i] は i 以下の数の出現数を示す
        for (long k=1; k<DIGIT; k++) {
            bin[k] += bin[k-1];
        }
        // converted の各要素について末尾から収まるべき位置に収納していく
        char** tmp = (char**)malloc(sizeof (char*) * n);
        for (long i=0; i<n; i++) tmp[i] = converted[i];
        for (long i=n-1; i>=0; i--) {
            converted[bin[(tmp[i][j] - '0')] - 1] = tmp[i];
            bin[(tmp[i][j] - '0')]--;
        }
        // この時点で converted は文字列化がなされた状態で、上 j+1 桁についてのソートがなされている
        // tmp は参照を借用しているのみ。参照先を開放してはいけない
        free(tmp);
    }
    // converted は文字列化がなされた状態で、全桁についてのソートがなされている
    for (long i=0; i<n; i++) {
        arr[i] = atoi(converted[i]);
    }
    // charのポインタのポインタなのであった。参照先を開放することを担う
    nested_free(converted, n);
}
