#ifdef AOC_INCLUDEME 
{
	FILE* input_file = fopen(filepath, "rb");
	if (input_file == NULL) {
		printf("could not open %s\n", filepath);
		exit(EXIT_FAILURE);
	}
	fseek(input_file, 0, SEEK_END);
	input_size = ftell(input_file);
	rewind(input_file);
	input = malloc(input_size);
	fread(input, sizeof(char), input_size, input_file);
	fclose(input_file);
}
#endif
