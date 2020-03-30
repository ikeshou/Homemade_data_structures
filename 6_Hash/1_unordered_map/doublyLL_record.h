#pragma once
#include <stdbool.h>
#include "struct_for_hash.h"


record_t make_record(char*, double);

DoublyLL_t make_empty_doubly_ll(void);

bool is_empty(DoublyLL_t);

void print_doubly_ll(DoublyLL_t);

void push_front(DoublyLL_t, const record_t);

cons pop_front(DoublyLL_t);

void push_back(DoublyLL_t, const record_t);

cons pop_back(DoublyLL_t);

cons_t insert_rec(DoublyLL_t, cons_t, record_t);

void delete_cons(DoublyLL_t, cons_t);

cons head(DoublyLL_t);

cons tail(DoublyLL_t);

cons_t find_rec_by_key(DoublyLL_t, char*);
