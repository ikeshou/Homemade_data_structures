#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>


/*
ascii_to_int_base_128("ab")
// => 12641 (97<'a'> * 128 + 98<'b'>= 12514)
*/
int ascii_to_int_base_128(char* str) {
    int n = strlen(str);
    int base = 128;
    int ans = 0;
    for (long i=n-1; i>=0; i--) {
        char c = str[i];
        ans += (long)(c * pow(base, (n-1-i)));
    }
    return ans;
}


/*
int_to_ascii_to_int(12)
// => ascii_to_int_base_128("12")
// => 6322 (49 <'1'> * 128 + 50 <'2'>= 6322)
*/
int int_to_ascii_to_int(int num) {
    int digit = (int)log10((double)num);
    char* s = (char*)malloc(sizeof(char) * digit+2);    // 必要な桁数は digit+1, それにNULL分の+1
    if (s == NULL) {
        fprintf(stderr, "int_to_ascii_to_int() in %s: cannot allocate a memory to string\n", __FILE__);
        exit(-1);
    }
    for (int i=0; i<=digit; i++) {
        s[i] = '0' + ((num / (int)pow(10, digit-i)) % 10);    // '2' などの '文字' に
    }
    s[digit+1] = '\0';
    int ans = ascii_to_int_base_128(s);
    free(s);
    return ans;
}


/*
bit mask のデバッグ用
*/
void putb(unsigned int v) {
    putchar('0');
    putchar('b');
    // v の bit 表記でのサイズを計算し、その最大桁に bit flag を立てる
    unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);
    // mask が 最小桁を通り過ぎるまで順にシフトしていき、各桁が 1 となっているかチェックして出力する
    do {
        putchar(mask & v ? '1' : '0');
    } while (mask >>= 1);
    printf("\n");
}


/*
h(k) = k mod m
ハッシュの負荷率 α = (要素数 n) / (テーブルサイズ m)
法の m に 2 ^ pや 2 ^ p -1 といった数値を選ぶのは<相応しくない>
2 の冪乗から離れた素数を選ぶと良い。
要素数 2000 個くらいを考え、一様ハッシュを仮定すると m = 701 だと平均 3 回衝突するとがわかる。
許容範囲内なので今回は m = 701 を採用。
*/
int devision_hash(int k) {
    int m = 701;
    return k % m;
}


/*
h(k) = floor(m * ((k * A) % 1)) (0 < A < 1)
(k * A) % 1 = (k * A の小数部分)
m は重要ではないビットシフトで計算しやすいよう m = 2 ^ p を採用する。
k を w[bit] で表される整数、A は A = s / 2 ^ w で表される分数とする。
A はどのように選択しても動くが、A が (√5 - 1) / 2 に近いと良い。(by Knuth)
このとき計算は簡単！
k が w[bit], s が w[bit] なので k * s は 2 * w[bit]
k * A の計算のためには 2 ^ w で割る必要があり、上記を w[bit] 右シフトすれば良い。このはみ出る部分が小数部分
さらに m = 2 ^ p をかけるのでこのうちの上位 p[bit] が整数部分として戻ってくる。floor()をとるのでこの p[bit] がハッシュ値となる。
今回は p = 10, m = 2 ^ 10, w = 32, A = 2654435769 / 2 ^ 32 を採用。
*/
int multiplication_hash(float k) {
    int p = 10;
    int w = 32;
    uint32_t s = 2654435769;
    uint32_t bit_mask = 0b0;
    for (int i=w-1; i>=w-p; i--) {
        bit_mask |= (1 << i);
    }
    // printf("%d\n", k * s);
    // putb(k * s);
    // putb(bit_mask);
    // putb(k * s & bit_mask);
    // putb((k * s & bit_mask) >> (w-p));
    return ((uint32_t)(k * s) & bit_mask) >> (w-p);
}
