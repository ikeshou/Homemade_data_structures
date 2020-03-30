#include <stdbool.h>


struct cell {
    double num;
    struct cell* next;
};
typedef struct cell cons, *cons_t;


typedef struct {
    cons_t head;
} LinkedList, *LinkedList_t;


LinkedList_t make_empty_linked_list(void);

bool is_empty(LinkedList_t);

void print_linked_list(LinkedList_t);

void push(LinkedList_t, const double);

cons pop(LinkedList_t);

cons head(LinkedList_t);

cons_t find(LinkedList_t, double);
