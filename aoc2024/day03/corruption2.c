#include "../c-parsley/includeme.h"

int main(int argc, char* argv[])
{
	// read input
	char* input;
	size_t input_size;
	read_file("input.txt", &input, &input_size);
	
	const char* dont_mul = "don't()";
	const char* do_mul = "do()";
	char* parse_pos = input;
	while (parse_pos = strstr(parse_pos, dont_mul)) {
		char* targ = strstr(parse_pos + 1, do_mul);
		if (targ == NULL) targ = &input[input_size - 2];
		while (parse_pos < targ) {
			*(parse_pos++) = 'X';
		}
		parse_pos++;
	}
	
	const char* mul = "mul(";
	int64_t total = 0;
	parse_pos = input;
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
