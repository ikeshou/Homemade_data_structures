#include <stdbool.h>


struct cell {
    double num;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;
    cons_t tail;
} CircularLL, *CircularLL_t;


CircularLL_t make_empty_circular_ll(void) ;

bool is_empty(CircularLL_t);

void print_circular_ll(CircularLL_t);

void push_front(CircularLL_t, const double);

cons pop_front(CircularLL_t);

void push_back(CircularLL_t, const double);

cons head(CircularLL_t);

cons tail(CircularLL_t);

cons_t find(CircularLL_t, double);
