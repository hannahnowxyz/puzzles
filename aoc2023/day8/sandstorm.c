// https://adventofcode.com/2023/day/8

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct node {
    uint64_t id;
    size_t left_index;
    size_t right_index;
};

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
    printf("instructions length: %d\n", instructions_len);
    
    size_t nodes_start_index = instructions_len + 2;
    size_t line_len = 0;
    while (input[nodes_start_index + line_len++] != '\n'); line_len--;
    printf("line length (not incl. newline): %d\n", line_len);

    size_t num_nodes = (input_size - instructions_len - 1)/(line_len + 1);
    printf("num nodes: %d\n", num_nodes);

    struct node* network = malloc((num_nodes + 1)*sizeof(struct node));
    memset(network, 0, sizeof(network));
    size_t start_index = 0, end_index = 0;

    // create network
    {
    #define LINEAR_SEARCH(TARG) for (i = 0; network[i].id != TARG && network[i].id != 0; i++) 
    
    char* parse_pos = input + nodes_start_index;
    uint64_t node_id = 0, left_id = 0, right_id = 0;
    size_t i = 0;

    for (size_t n = 0; n < num_nodes; n++)
    {
	sscanf(parse_pos, "%3c = (%3c, %3c)", &node_id, &left_id, &right_id);
	if (n < 5) printf("parsed %d %d %d\n", node_id, left_id, right_id);
	parse_pos += line_len + 1;
	
	// parent node known?
	LINEAR_SEARCH(node_id);
	size_t node_index = i;
	network[node_index].id = node_id;
	
	// left node known?
	LINEAR_SEARCH(left_id);
	if (network[i].id == 0) network[i].id = left_id;
	network[node_index].left_index = i;
	
	// right node known?
	LINEAR_SEARCH(right_id);
	if (network[i].id == 0) network[i].id = right_id;
	network[node_index].right_index = i;
    }

    printf("network:");
    for (size_t i = 0; i < 5; i++) {
	printf(" {%d %d %d}",
	    network[i].id,
            network[i].left_index,
	    network[i].right_index
	);
    }
    printf("...\n");

    uint64_t start_id = 0, end_id = 0;
    sscanf("AAA", "%3c", &start_id);
    sscanf("ZZZ", "%3c", &end_id);
    LINEAR_SEARCH(start_id);
    start_index = i;
    printf("start index: %d\n", start_index);
    LINEAR_SEARCH(end_id);
    end_index = i;
    printf("end_index: %d\n", end_index);

    #undef LINEAR_SEARCH
    }

    // compute path length
    uint64_t curr_index = start_index;
    size_t curr_step = 0;
    printf("path: %d", start_index);
    while (curr_index != end_index) {
	if (input[curr_step++ % instructions_len] == 'L')
	    curr_index = network[curr_index].left_index;
	else
	    curr_index = network[curr_index].right_index;
	if (curr_step < 10) printf(" > %d", curr_index);
    }
    printf("...\n");

    // print solution
    free(input);
    free(network);
    printf("path length: %d\n", curr_step);
    return 0;
}
