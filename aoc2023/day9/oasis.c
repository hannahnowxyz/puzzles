#define AOC_MAIN
#include "../c_includeme/includeme.h"

int main(int argc, char* argv[])
{
    // read input
    unsigned char* input = NULL;
    struct line* lines = NULL;
    size_t num_lines = 0;
    unsigned char delim = ' ';
    size_t max_tokens = 0;
    #include "../c_includeme/parseme.c"

    // parse input
    uint64_t** histories = malloc(num_lines*sizeof(uint64_t*));
    for (size_t i = 0; i < num_lines; i++) {
	histories[i] = malloc(lines[i].num_tokens*sizeof(uint64_t));
	char* parse_pos = lines[i].cstr_ptr;
    	for (size_t t = 0; t < lines[i].num_tokens; t++) {
	    sscanf(parse_pos, "%d", &histories[i][t]);
	    parse_pos = strchr(parse_pos, delim) + 1;
	}
    }

    // compute solution
    uint64_t grand_sum = 0;
    for (size_t i = 0; i < num_lines; i++) {
    	for (size_t q = 0; q < lines[i].num_tokens - 1; q++) {
	    for (size_t j = 0; j < lines[i].num_tokens - q - 1; j++) {
	        histories[i][j] = histories[i][j + 1] - histories[i][j];
	    }
	    grand_sum += histories[i][lines[i].num_tokens - q - 1];
	}
    }

    free(input);
    for (size_t i = 0; i < num_lines; i++) {
	free(histories[i]);
    }
    free(histories);
    printf("solution: %d\n", grand_sum);
    return 0;
}
