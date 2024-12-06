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
	
	const size_t num_cols = lines[0].length;
	// create 2d array over input (+1 for nulls)
	char (*matrix)[num_cols + 1] = (void*)input;
	const char XMAS[] = "XMAS";
	const char SAMX[] = "SAMX";
	#define MORE_XMAS(s) (!memcmp(s, XMAS, 4) || !memcmp(s, SAMX, 4))
	size_t thats_a_lotta_XMAS = 0;
	
	// check vertical
	for (size_t i = 0; i <= num_lines - 4; i++) {
		for (size_t j = 0; j <= num_cols - 1; j++) {
			char curr_string[] = {
				matrix[i][j],
				matrix[i + 1][j],
				matrix[i + 2][j],
				matrix[i + 3][j]
			};
			thats_a_lotta_XMAS += MORE_XMAS(curr_string);
		}
	}
	
	// check horizontal
	for (size_t i = 0; i <= num_lines - 1; i++) {
		for (size_t j = 0; j <= num_cols - 4; j++) {
			char curr_string[] = {
				matrix[i][j],
				matrix[i][j + 1],
				matrix[i][j + 2],
				matrix[i][j + 3]
			};
			thats_a_lotta_XMAS += MORE_XMAS(curr_string);
		}
	}
	
	// check \ diagonal
	for (size_t i = 0; i <= num_lines - 4; i++) {
		for (size_t j = 0; j <= num_cols - 4; j++) {
			char curr_string[] = {
				matrix[i][j],
				matrix[i + 1][j + 1],
				matrix[i + 2][j + 2],
				matrix[i + 3][j + 3]
			};
			thats_a_lotta_XMAS += MORE_XMAS(curr_string);
		}
	}
	
	// check / diagonal
	for (size_t i = 0; i <= num_lines - 4; i++) {
		for (size_t j = 3; j <= num_cols; j++) {
			char curr_string[] = {
				matrix[i][j],
				matrix[i + 1][j - 1],
				matrix[i + 2][j - 2],
				matrix[i + 3][j - 3]
			};
			thats_a_lotta_XMAS += MORE_XMAS(curr_string);
		}
	}
	
	#undef MORE_XMAS
	
	free(lines);
	free(input);
	printf("solution: %zu\n", thats_a_lotta_XMAS);
	return 0;
}
