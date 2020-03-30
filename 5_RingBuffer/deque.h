#include <stdbool.h>


typedef struct {
    long capacity;
    long size;
    long head_ind;
    long tail_ind;
    double* arr;
} deque, *deque_t;


deque_t make_deque(void);

long capacity(deque_t);

long size(deque_t);

bool is_empty(deque_t);

void print_deque(deque_t);

void traverse_deque(deque_t);

long next_tail_ind(deque_t);

long previous_tail_ind(deque_t);

long next_head_ind(deque_t);

long previous_head_ind(deque_t);

void push_back(deque_t, const double);

double pop_back(deque_t);

void push_front(deque_t, const double);

double pop_front(deque_t);

double at(deque_t, const long);

double front(deque_t);

double back(deque_t);

double* begin(deque_t);

double* end(deque_t);