#ifdef PARSLEY_H

// read entire input file into memory
void read_file(const char* filepath, char** out_data, size_t* out_size)
{
	FILE* input_file = fopen(filepath, "rb");
	if (input_file == NULL) {
		printf("could not open %s\n", filepath);
		exit(EXIT_FAILURE);
	}
	fseek(input_file, 0, SEEK_END);
	size_t input_size = ftell(input_file);
	rewind(input_file);

	// pad for files without terminating newline
	char* input = malloc(input_size + 1);
	fread(input, sizeof(char), input_size, input_file);
	fclose(input_file);

	*out_data = input;
	*out_size = input_size;
	return;
}

// break up input text into an array of c-strings (destructive)
void parse_input(
	char* input,
	const size_t input_size,
	const char line_delim,
	const char token_delim,
	struct line** out_lines,
	size_t* out_num_lines,
	size_t* out_max_tokens
) {
	struct line* lines = NULL;
	size_t num_lines = 0;
	size_t max_tokens = 0;
	
	// replace all newlines with nulls
	input[input_size] = '\0';
	num_lines = input[input_size - 1] != line_delim;
	size_t parse_index = input_size - 1;
	while (parse_index) {
		unsigned char is_newline = input[parse_index] == line_delim;
		input[parse_index] &= is_newline - 1;
		num_lines += is_newline;
		parse_index--;
	}
	
	// initialize line struct array
	lines = malloc(num_lines*sizeof(struct line));
	for (size_t i = 0; i < num_lines; i++) {
	 	lines[i].cstr_ptr = &input[parse_index];
		lines[i].length = 0;
		lines[i].num_tokens = *lines[i].cstr_ptr != '\0';
		bool new_token = true;
		while (input[parse_index]) {
			lines[i].num_tokens += new_token && input[parse_index] == token_delim;
			lines[i].length++;
			parse_index++;
			new_token = input[parse_index - 1] != token_delim;
		}
		if (lines[i].num_tokens > max_tokens) {
			max_tokens = lines[i].num_tokens;
		}
		parse_index++;
	}
	
	*out_lines = lines;
	*out_num_lines = num_lines;
	*out_max_tokens = max_tokens;
	return;
}

#endif
