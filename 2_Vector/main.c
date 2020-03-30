#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "elastic_array.h"


int main(void) {
    srand(time(NULL));
    vector_t vec_t = make_vector();

    print_vector(vec_t);    // vector:
    printf("is empty?... %s\n", is_empty(vec_t) ? "true" : "false");    // true
    push_back(vec_t, (double)rand()/RAND_MAX);
    print_vector(vec_t);    // vector: 0.027
    printf("is empty?...%s\n", is_empty(vec_t) ? "true" : "false");    // false
    pop_back(vec_t);
    print_vector(vec_t);    // vector:
    printf("is empty?...%s\n", is_empty(vec_t) ? "true" : "false");    // true
    
    printf("----------------\n");
    for (int i=0; i<10; i++) {
        push_back(vec_t, (double)rand()/RAND_MAX);
        print_vector(vec_t);
    }
    printf("----------------\n");

    while (!is_empty(vec_t))
    {
        pop_back(vec_t);
    }
    printf("after clear\n");
    print_vector(vec_t);
    printf("is empty?...%s\n", is_empty(vec_t) ? "true" : "false");
    
    return 0;
}