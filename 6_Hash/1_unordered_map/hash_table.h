#pragma once
#include "hash_func.h"
#include "struct_for_hash.h"
#include "doublyLL_record.h"


int hash_key(char*);

chained_hashtab_t make_chained_hash_table(void);

void print_chained_hash(chained_hashtab_t);

void chained_hash_insert(chained_hashtab_t, record_t);

double chained_hash_search(chained_hashtab_t, char*);

void chained_hash_delete(chained_hashtab_t, char*);
