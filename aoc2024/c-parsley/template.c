#include "../c-parsley/includeme.h"

int main(int argc, char* argv[])
{
	char* input;
	size_t input_size;
	read_file("input.txt", &input, &input_size);
	
	struct line* lines;
	size_t num_lines;
	size_t max_tokens;
	parse_input(input, input_size, '\n', ' ', &lines, &num_lines, &max_tokens);
	
	// TODO compute solution

	free(lines);
	free(input);
	printf("solution: %d\n", 0);
	return 0;
}
