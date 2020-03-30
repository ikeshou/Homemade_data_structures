#include <stdbool.h>

typedef struct {
    long size;
    long max_size;
    double* arr;
} heap, *heap_t;


void swap(double*, double*);

heap_t make_empty_heap(void);

bool is_empty(heap_t);

void print_heap(heap_t);

void expand_heap(heap_t, long);

void max_heapify(heap_t, long);

heap_t build_max_heap(double*, long);

double peek_maximum(heap_t);

void max_heap_change_num(heap_t, long, double);

void max_heap_insert(heap_t, double);

double extract_max(heap_t);

void heap_sort(double*, long);
