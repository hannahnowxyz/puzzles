// allow compiling alone for testing purposes
#ifndef AOC_MAIN
#include "includeme.h"
int main(int argc, char* argv[])
{
    // must be pre-defined in including file
    unsigned char* input = NULL;
    struct line* lines = NULL;
    size_t num_lines = 0;
    unsigned char delim = ' ';
    size_t max_tokens = 0;
#endif
    {// prevent leaking variables
    
    // read entire input file in memory
    FILE* input_file = fopen("input.txt", "rb");
    if (input_file == NULL) {
    	printf("could not open input.txt");
	exit(1);
    }
    fseek(input_file, 0, SEEK_END);
    size_t input_size = ftell(input_file);
    rewind(input_file);
    // pad for files without terminating newline
    input = malloc(input_size + 1);
    fread(input, sizeof(char), input_size, input_file);
    fclose(input_file);
    
    // replace all newlines with nulls
    input[input_size] = '\0';
    num_lines = input[input_size - 1] != '\n';
    size_t parse_index = input_size - 1;
    {
    unsigned char is_newline = 0;
    while (parse_index) {
	is_newline = input[parse_index] == '\n';
	input[parse_index] &= is_newline - 1;
	num_lines += is_newline;
	parse_index--;
    }}

    // initialize line struct array
    lines = malloc(num_lines*sizeof(struct line));
    for (size_t i = 0; i < num_lines; i++) {
	lines[i].cstr_ptr = &input[parse_index];
	lines[i].length = 0;
	lines[i].num_tokens = 1;
	while (input[parse_index]) {
	    lines[i].num_tokens += input[parse_index] == delim;
	    lines[i].length++;
	    parse_index++;
	}
	if (lines[i].num_tokens > max_tokens) {
	    max_tokens = lines[i].num_tokens;
	}
	parse_index++;
    }

    }// prevent leaking variables
#ifndef AOC_MAIN
    printf(
	"read %d lines, max %d tokens:\n",
	num_lines,
	max_tokens
    );
    for (size_t i = 0; i < num_lines; i++) {
	printf(
	    "(%3d tokens, %3d bytes) \"%s\"\n",
	    lines[i].num_tokens,
	    lines[i].length,
	    lines[i].cstr_ptr
	);
    }
    free(input);
    return 0;
}
#endif
