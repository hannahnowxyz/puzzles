// does not work for actual problem >_< graph is cyclic

#include "../c-parsley/includeme.h"

struct pagerule {
	size_t left;
	size_t right;
	size_t right_index;
	bool resolved;
};

int szt_cmp(const void* a, const void* b) {
	size_t au = *(const size_t*)a;
	size_t bu = *(const size_t*)b;
	return (au > bu) - (au < bu);
}

int pgr_cmp(const void* a, const void* b) {
	struct pagerule au = *(const struct pagerule*)a;
	struct pagerule bu = *(const struct pagerule*)b;
	return (au.left > bu.left) - (au.left < bu.left);
}

int main(int argc, char* argv[])
{
	char* input;
	size_t input_size;
	read_file("input2.test", &input, &input_size);
	
	struct line* lines;
	size_t num_lines;
	size_t max_tokens;
	parse_input(input, input_size, '\n', ',', &lines, &num_lines, &max_tokens);
	
	// parse rules
	size_t num_rules = num_lines;
	while (lines[--num_rules].num_tokens);
	struct pagerule* rulebook = malloc(sizeof(struct pagerule)*num_rules);
	for (size_t i = 0; i < num_rules; i++) {
		sscanf(lines[i].cstr_ptr, "%zu|%zu", &rulebook[i].left, &rulebook[i].right);
		rulebook[i].resolved = false;
	}
	printf("parsed %zu rules\n", num_rules);
	
	// parse lists of pages
	size_t num_pagelists = num_lines - num_rules - 1;
	size_t pagelists_start_index = num_rules + 1;
	size_t** pagelists = malloc(sizeof(size_t*)*num_pagelists);
	for (size_t p = 0; p < num_pagelists; p++) {
		pagelists[p] = malloc(sizeof(size_t)*lines[pagelists_start_index + p].num_tokens);
	}
	for (size_t p = 0; p < num_pagelists; p++) {
		char* parse_pos = lines[pagelists_start_index + p].cstr_ptr;
		sscanf(parse_pos, "%zu", &pagelists[p][0]);
		for (size_t t = 1; t < lines[pagelists_start_index + p].num_tokens; t++) {
			parse_pos = strchr(parse_pos, ',') + 1;
			sscanf(parse_pos, "%zu", &pagelists[p][t]);
		}
	}
	printf("parsed %zu pagelists\n\n", num_pagelists);
	
	// add extra right-of-none rules, this allows a simplifying assumption
	size_t max_relevant_page = 99; // cheaty value from manual inspection
	size_t num_ruled_pages = 0; // unclever initial upper bound
	size_t* aux_stack = malloc(sizeof(size_t)*(max_relevant_page + 1));
	memset(aux_stack, 0, sizeof(size_t)*(max_relevant_page + 1));
	for (size_t i = 0; i < num_rules; i++) {
		num_ruled_pages += !aux_stack[rulebook[i].left];
		num_ruled_pages += !aux_stack[rulebook[i].right];
		aux_stack[rulebook[i].left] += aux_stack[rulebook[i].left] == 0;
		aux_stack[rulebook[i].right] = 2;
	}
	size_t num_right_of_none = 0;
	{
		size_t* right_of_none = malloc(sizeof(size_t)*num_ruled_pages);
		for (size_t i = 0; i < num_rules; i++) {
			size_t curr_page = rulebook[i].left;
			if (aux_stack[curr_page] != 2) {
				right_of_none[num_right_of_none++] = curr_page;
				aux_stack[curr_page] = 2;
			}
		}
		rulebook = realloc(rulebook, sizeof(struct pagerule)*(num_rules + num_right_of_none));
		for (size_t i = 0; i < num_right_of_none; i++) {
			struct pagerule extra_rule = {.right = right_of_none[i]};
			rulebook[num_rules + i] = extra_rule;
		}
		num_rules += num_right_of_none;
		num_ruled_pages++; // zero is now ruled
		free(right_of_none);
	}
	
	// sort and add traversal-helping index data
	qsort(rulebook, num_rules, sizeof(struct pagerule), pgr_cmp);
	for (size_t i = 0; i < num_rules; i++) {
		struct pagerule key = {.left = rulebook[i].right};
		void* res = bsearch(&key, rulebook, num_rules, sizeof(struct pagerule), pgr_cmp);
		if (res == NULL) {
			rulebook[i].right_index = num_rules;
		} else {
			size_t found_at = (struct pagerule*)res - rulebook;
			while (found_at > 0 && rulebook[found_at - 1].left == rulebook[found_at].left) found_at--;
			rulebook[i].right_index = found_at;
		}
	}
	
	printf("computed rulebook:\n");
	for (size_t i = 0; i < num_rules; i++) {
		printf(
			"%4zu: %2zu -> %2zu(@%zu)\n",
			i,
			rulebook[i].left,
			rulebook[i].right,
			rulebook[i].right_index
		);
	}
	printf("\n");
	
	// topological sort
	size_t* topo_sorted_pages = malloc(sizeof(size_t)*num_ruled_pages);
	topo_sorted_pages[0] = 0;
	{
		size_t prepend_index = num_ruled_pages;
		
		for (size_t i = 0; i < num_right_of_none; i++)
		{
			printf("sorting from rule %zu:\n\n", i);
			size_t curr_rule = i;
			size_t stack_top = 0;
			aux_stack[stack_top++] = curr_rule;
			
			while (stack_top)
			{
				printf("current rule stack:");
				for (size_t k = 0; k < stack_top; printf(" %zu", aux_stack[k++]));
				printf("\n");
				curr_rule = aux_stack[--stack_top];
				printf("popped %zu:", curr_rule);
				if (!rulebook[curr_rule].resolved)
				{
					// searching for a page that is left-of-none
					if (rulebook[curr_rule].right_index == num_rules)
					{
						// mark all rules that .right to this page as resolved
						printf(" left of none, resolved");
						topo_sorted_pages[--prepend_index] = rulebook[curr_rule].right;
						for (size_t k = 0; k < num_rules; k++) {
							if (rulebook[k].right == rulebook[curr_rule].right) {
								rulebook[k].resolved = true;
								printf(" %zu", k);
							}
						}
						printf(", exposed");
						
						// update which pages are left-of-none
						for (size_t k = 0; k < num_rules;) {
							bool all_resolved = true;
							size_t run_length = 0;
							do {
								all_resolved &= rulebook[k + run_length].resolved;
								run_length++;
							} while (
								k + run_length < num_rules
								&& rulebook[k + run_length - 1].left == rulebook[k + run_length].left
							);
							if (all_resolved) {
								for (size_t l = 0; l < num_rules; l++) {
									if (rulebook[l].right == rulebook[k].left) {
										if (rulebook[l].right_index == num_rules) break;
										rulebook[l].right_index = num_rules;
										printf(" %zu", l);
									}
								}
							}
							k += run_length;
						}
						printf("\nupdated rulebook:\n");
						for (size_t i = 0; i < num_rules; i++) {
							printf(
								"%4zu%c %2zu -> %2zu(@%zu)\n",
								i,
								rulebook[i].resolved ? '*' : ':',
								rulebook[i].left,
								rulebook[i].right,
								rulebook[i].right_index
							);
						}
						printf("\n");
					}
					else {
						printf(" left of some, pushed");
						aux_stack[stack_top++] = curr_rule;
						printf(" %zu", curr_rule);
						curr_rule = rulebook[curr_rule].right_index;
						size_t run_length = 0;
						do {
							aux_stack[stack_top++] = curr_rule + run_length;
							printf(" %zu", curr_rule + run_length);
							run_length++;
						} while (
							curr_rule + run_length < num_rules
							&& rulebook[curr_rule + run_length - 1].left == rulebook[curr_rule + run_length].left
						);
						printf("\n");
					}
				}
				else printf(" (resolved)\n");
			}
		}
	}
	
	printf("topologically sorted pages: [");
	for (size_t i = 0; i < num_ruled_pages - 1; printf("%zu ", topo_sorted_pages[i++]));
	printf("%zu]\n\n", topo_sorted_pages[num_ruled_pages - 1]);
	
	// from computed sorting compute total ordering of all relevant pages
	memcpy(aux_stack, topo_sorted_pages, sizeof(size_t)*num_ruled_pages);
	qsort(aux_stack, num_ruled_pages, sizeof(size_t), szt_cmp);
	size_t* totally_ordered_pages = malloc(sizeof(size_t)*(max_relevant_page + 1));
	for (size_t r = 0; r <= max_relevant_page; r++) {
		totally_ordered_pages[r] = r;
	}
	for (size_t j = 0; j < num_ruled_pages; j++) {
		totally_ordered_pages[aux_stack[j]] = topo_sorted_pages[j];
	}
	
	printf("computed total ordering: [");
	for (size_t r = 0; r < max_relevant_page; printf("%zu ", totally_ordered_pages[r++]));
	printf("%zu]\n\n", totally_ordered_pages[max_relevant_page]);
	
	// check if each list of pages satisfies computed ordering
	uint64_t middle_sum = 0;
	for (size_t p = 0; p < num_pagelists; p++) {
		bool sat = true;
		size_t searchfrom_index = 0;
		for (size_t t = 0; t < lines[pagelists_start_index + p].num_tokens; t++) {
			// linear search ahead for current page:
			// if not found, then it was skipped over previously,
			// and hence ordering not satisfied
			bool page_found_ahead = false;
			for (size_t r = searchfrom_index; r <= max_relevant_page; r++) {
				if (totally_ordered_pages[r] == pagelists[p][t]) {
					page_found_ahead = true;
					searchfrom_index = r + 1;
					break;
				}
			}
			if (!(sat &= page_found_ahead)) break;
		}
		if (sat) middle_sum += pagelists[p][lines[pagelists_start_index + p].num_tokens/2];
	}
	
	free(totally_ordered_pages);
	free(topo_sorted_pages);
	free(aux_stack);
	for (size_t p = 0; p < num_pagelists; free(pagelists[p++]));
	free(pagelists);
	free(rulebook);
	free(lines);
	free(input);
	printf("solution: %" PRIu64 "\n", middle_sum);
	return 0;
}
