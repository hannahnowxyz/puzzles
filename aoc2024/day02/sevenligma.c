#include "../c-parsley/includeme.h"

bool is_report_safe(int* report, size_t report_len)
{
	int monotonic_sign = (report[1] > report[0]) - (report[1] < report[0]);
	for (size_t t = 0; t < report_len - 1; t++) {
		int delta = (report[t + 1] - report[t])*monotonic_sign;
		if (delta <= 0 || delta > 3) return false;
	}

	return true;
}

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
	
	// brute force solution
	size_t num_safe_reports = 0;
	for (size_t i = 0; i < num_lines; i++)
	{
		size_t n = lines[i].num_tokens;
		char* parse_pos = lines[i].cstr_ptr;
		int report[n];
		sscanf(parse_pos, "%d", &report[0]);
		for (size_t t = 1; t < n; t++) {
			parse_pos = strchr(parse_pos, ' ') + 1;
			sscanf(parse_pos, "%d", &report[t]);
		}
		
		if (n < 3 || is_report_safe(report, n)) {
			num_safe_reports++;
			continue;
		}
		
		size_t omit_index = 0;
		int report_copy[n];
		while (omit_index < n) {
			memcpy(report_copy, report, sizeof(int)*n);
			int swap = report_copy[omit_index];
			for (size_t t = omit_index; t < n - 1; t++) {
				report_copy[t] = report_copy[t + 1];
			}
			report_copy[n - 1] = swap;
			if (is_report_safe(report_copy, n - 1)) break;
			omit_index++;
		}
		
		num_safe_reports += omit_index < n;
	}
	
	free(lines);
	free(input);
	printf("solution: %zu\n", num_safe_reports);
	return 0;
}
