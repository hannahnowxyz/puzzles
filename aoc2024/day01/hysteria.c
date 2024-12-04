#define AOC_MAIN
#include "../c_includeme/includeme.h"

int u64_cmp(const void* a, const void* b) {
    uint64_t au = *(const uint64_t*)a;
    uint64_t bu = *(const uint64_t*)b;
    return (au > bu) - (au < bu);
}

int main(int argc, char* argv[])
{
    // read input
    #include "../c_includeme/parseme.c"

    uint64_t list_a[num_lines];
    uint64_t list_b[num_lines];
    for (size_t i = 0; i < num_lines; i++) {
        sscanf(lines[i].cstr_ptr, "%" SCNu64 "%" SCNu64, &list_a[i], &list_b[i]);
    }
    qsort(list_a, num_lines, sizeof(list_a[0]), u64_cmp);
    qsort(list_b, num_lines, sizeof(list_b[0]), u64_cmp);

    uint64_t total_distance = 0;
    for (size_t i = 0; i < num_lines; i++) {
        uint64_t a = list_a[i];
        uint64_t b = list_b[i];
        if (a > b) total_distance += a - b;
        else total_distance += b - a;
    }

    free(lines);
    free(input);
    printf("solution: %" PRIu64 "\n", total_distance);
    return 0;
}
