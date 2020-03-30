#include <stdbool.h>


typedef struct {
    char name;
    double key;
} record, *record_t;


typedef struct {
    long size;
    long max_size;
    record* arr;
} pqueue, *pqueue_t;


void swap(record_t, record_t);

pqueue_t make_empty_pqueue(void);

void print_pqueue(pqueue_t);

bool is_empty(pqueue_t);

void expand_pqueue(pqueue_t, long);

void max_pqueate(pqueue_t, long);

record peek_maximum(pqueue_t);

void max_pqueue_change_num(pqueue_t, long, double);

void max_pqueue_insert(pqueue_t, record);

record extract_max(pqueue_t);

