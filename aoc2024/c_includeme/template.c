#define AOC_MAIN
#include "../c_includeme/includeme.h"

int main(int argc, char* argv[])
{
    // read input
    #include "../c_includeme/parseme.c"

    // TODO compute solution

    free(lines);
    free(input);
    printf("solution: %d\n", 0);
    return 0;
}
