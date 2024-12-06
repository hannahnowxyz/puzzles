#include "../c-parsley/includeme.h"

int main(int argc, char* argv[])
{
	// read input
	char* input;
	size_t input_size;
	read_file("input.txt", &input, &input_size);
	
	struct line* lines;
	size_t num_lines;
	size_t max_tokens;
	parse_input(input, input_size, '\n', ' ', &lines, &num_lines, &max_tokens);
	
	size_t num_unsafe = 0;
	for (size_t i = 0; i < num_lines; i++)
	{
		size_t n = lines[i].num_tokens;
		if (n < 2) continue;
		
		int report[n];
		char* parse_pos = lines[i].cstr_ptr;
		sscanf(parse_pos, "%d%d", &report[0], &report[1]);
		int monotonic_sign = (report[1] > report[0]) - (report[1] < report[0]);
		if (monotonic_sign == 0) {
			num_unsafe++;
			continue;
		}
		
		for (size_t t = 0; t < n - 1; t++) {
			parse_pos = strchr(parse_pos, ' ') + 1;
			sscanf(parse_pos, "%d", &report[t + 1]);
			int delta = (report[t + 1] - report[t])*monotonic_sign;
			if (delta <= 0 || delta > 3) {
				num_unsafe++;
				break;
			}
		}
	}
	
	free(lines);
	free(input);
	printf("solution: %zu\n", num_lines - num_unsafe);
	return 0;
}
