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
    #include "parseme.c"

    // TODO compute solution

    free(input);
    printf("solution: %d\n", 0);
    return 0;
}
