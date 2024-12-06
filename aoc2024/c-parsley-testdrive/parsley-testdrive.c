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
	
	printf(
		"read %zu lines, max %zu tokens:\n",
		num_lines,
		max_tokens
	);
	for (size_t i = 0; i < num_lines; i++) {
		printf(
			"(%3zu tokens, %3zu bytes) \"%s\"\n",
			lines[i].num_tokens,
			lines[i].length + 1,
			lines[i].cstr_ptr
		);
	}
	free(lines);
	free(input);
	return 0;
}
