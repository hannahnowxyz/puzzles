// https://adventofcode.com/2023/day/8

// pretty sure this gets the right answer eventually,
// but never waited that long. obviously the wrong approach.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define ID_LEN 3

struct node {
    unsigned char id[ID_LEN];
    size_t left_index;
    size_t right_index;
};

void selection_sort(size_t* arr, size_t arr_len) {
    for (size_t i = 0; i < arr_len; i++) {
    	size_t mindex = i;
	for (size_t j = i; j < arr_len; j++)
	    if (arr[j] < arr[mindex]) mindex = j;
	size_t temp = arr[i];
	arr[i] = arr[mindex];
	arr[mindex] = temp;
    }
}

int main(int argc, char* argv[])
{
    // read input
    FILE* input_file = fopen("input.txt", "r");
    fseek(input_file, 0, SEEK_END);
    size_t input_size = ftell(input_file);
    rewind(input_file);
    char* input = malloc(input_size);
    fread(input, sizeof(char), input_size, input_file);
    fclose(input_file);

    // parse input
    size_t instructions_len = 0;
    while (input[instructions_len++] != '\n'); instructions_len--;
    size_t nodes_start_index = instructions_len + 2;
    size_t line_len = 0;
    while (input[nodes_start_index + line_len++] != '\n'); line_len--;
    size_t num_nodes = (input_size - instructions_len - 1)/(line_len + 1);

    struct node* network = malloc((num_nodes + 1)*sizeof(struct node));
    memset(network, 0, sizeof(network));
    size_t num_simul_paths = 0;

    // create network
    {
    char* parse_pos = input + nodes_start_index;
    unsigned char node_id[ID_LEN], left_id[ID_LEN], right_id[ID_LEN];
    size_t i = 0;

    #define LINEAR_SEARCH(TARG) for (i = 0; network[i].id != TARG && network[i].id != 0; i++)
    
    for (size_t n = 0; n < num_nodes; n++)
    {
	sscanf(parse_pos, "%3c = (%3c, %3c)", &node_id, &left_id, &right_id);
	parse_pos += line_len + 1;
	
	// parent node known?
	LINEAR_SEARCH(node_id);
	size_t node_index = i;
	memcpy(network[node_index].id, node_id, ID_LEN);

	// is start index?
	num_simul_paths += node_id[2] == 'A';
	
	// left node known?
	LINEAR_SEARCH(left_id);
	if (network[i].id == 0) memcpy(network[i].id, left_id, ID_LEN);
	network[node_index].left_index = i;
	
	// right node known?
	LINEAR_SEARCH(right_id);
	if (network[i].id == 0) memcpy(network[i].id, right_id, ID_LEN);
	network[node_index].right_index = i;
    }}
    
    #undef LINEAR_SEARCH
    
    printf("num simul. paths: %d\n", num_simul_paths);

    // find start and end indices
    size_t start_indices[num_simul_paths];
    size_t end_indices[num_simul_paths];
    size_t start_count = 0, end_count = 0;
    for (size_t i = 0; i < num_nodes; i++) {
	if (network[i].id[2] == 'A') start_indices[start_count++] = i;
	else if (network[i].id[2] == 'Z') end_indices[end_count++] = i;
    }

    selection_sort(end_indices, num_simul_paths);

    printf("start indices:");
    for (size_t i = 0; i < num_simul_paths; i++) printf(" %d", start_indices[i]);
    printf("\nend indices:");
    for (size_t i = 0; i < num_simul_paths; i++) printf(" %d", end_indices[i]);
    printf("\n");
    
    // compute path length
    size_t* curr_indices = start_indices;
    size_t curr_step = 0;
    bool all_matching = false;
    while (!all_matching) {
	if (input[curr_step++ % instructions_len] == 'L') {
	    for (size_t i = 0; i < num_simul_paths; i++)
		curr_indices[i] = network[curr_indices[i]].left_index;
	}
	else {
	    for (size_t i = 0; i < num_simul_paths; i++)
		curr_indices[i] = network[curr_indices[i]].left_index;
    	}
	selection_sort(curr_indices, num_simul_paths);
	all_matching = true;
	for (size_t i = 0; all_matching && i < num_simul_paths; i++)
            all_matching &= curr_indices[i] == end_indices[i];
    }

    // print solution
    free(input);
    free(network);
    printf("path length: %d\n", curr_step);
    return 0;
}
