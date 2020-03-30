#include <stdbool.h>


struct cell {
    double num;
    struct cell* previous;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;
    cons_t tail;
} DoublyLL, *DoublyLL_t;


DoublyLL_t make_empty_doubly_ll(void);

bool is_empty(DoublyLL_t);

void print_doubly_ll(DoublyLL_t);

void push_front(DoublyLL_t, const double);

cons pop_front(DoublyLL_t);

void push_back(DoublyLL_t, const double);

cons pop_back(DoublyLL_t);

cons_t insert(DoublyLL_t, cons_t, double);

void delete(DoublyLL_t, cons_t);

cons head(DoublyLL_t);

cons tail(DoublyLL_t);

cons_t find(DoublyLL_t, double);