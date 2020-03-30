typedef struct {
    char mark;
    long number;
} Card;


void counting_sort_trump(Card[], long);

void print_trump_array(Card[], long);

void counting_sort(long[], long, long);

void print_long_array(long[], long);

char* ltos(long, long);

void nested_free(char**, long);

void radix_sort(long[], long, long);

void print_char_array(char*[], long);