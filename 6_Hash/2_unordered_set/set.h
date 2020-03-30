#pragma once
#include <stdbool.h>
#include "hash_func.h"
#include "struct_for_set.h"
#include "doubly.h"


int hash_key(double);

chained_hashtab_t make_set(void);

void print_set(chained_hashtab_t);

void set_insert(chained_hashtab_t, double);

bool set_search(chained_hashtab_t, double);

void set_delete(chained_hashtab_t, double);
