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
	size_t thats_a_lotta_XMAS = 0;
	
	// check X
	// misread the problem: MUST be in cis-configuration
	for (size_t i = 1; i <= num_lines - 2; i++) {
		for (size_t j = 1; j <= num_cols - 2; j++) {
			thats_a_lotta_XMAS += (
				matrix[i][j] == 'A'
				&& (
					( (matrix[i - 1][j - 1] == 'M')
					+ (matrix[i - 1][j + 1] == 'M')
					+ (matrix[i + 1][j - 1] == 'M')
					+ (matrix[i + 1][j + 1] == 'M'))
					== 2
				) && (
					( (matrix[i - 1][j - 1] == 'S')
					+ (matrix[i - 1][j + 1] == 'S')
					+ (matrix[i + 1][j - 1] == 'S')
					+ (matrix[i + 1][j + 1] == 'S'))
					== 2
				) && (
					( (matrix[i - 1][j - 1] == 'M')
					+ (matrix[i + 1][j + 1] == 'M'))
					== 1
				)
			);
		}
	}
	
	free(lines);
	free(input);
	printf("solution: %zu\n", thats_a_lotta_XMAS);
	return 0;
}
