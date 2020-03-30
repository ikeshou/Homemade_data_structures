#include <stdbool.h>

typedef struct {
    long capacity; // 拡張なく入れることのできる要素数
    long size; // 現在の要素数
    double* arr;
} vector, *vector_t;


vector_t make_vector(void);

void push_back(vector_t, const double);

void pop_back(vector_t vec_t);

double at(vector_t, const long);

double front(vector_t);

double back(vector_t);

double* begin(vector_t);

double* end(vector_t);

long capacity(vector_t);

long size(vector_t);

bool is_empty(vector_t);

void print_vector(vector_t);