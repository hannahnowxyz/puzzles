#define AOC_MAIN
#include "../c_includeme/includeme.h"

int main(int argc, char* argv[])
{
	// read input
	const char* filepath = "input.txt";
	size_t input_size;
	char* input;
	#include "../c_includeme/readme.c"
	
	char* mul = "mul(";
	int64_t total = 0;
	char* parse_pos = input;
	unsigned int a;
	unsigned int b;
	unsigned int n;
	while (parse_pos = strstr(parse_pos, mul)) {
		bool parse_success = (
			sscanf(parse_pos, "mul(%3u,%3u%n", &a, &b, &n) == 2
			&& *(parse_pos + n) == ')'
		);
		if (parse_success) total += a*b;
		parse_pos++;
	}
	
	free(input);
	printf("solution: %" PRIi64 "\n", total);
	return 0;
}
