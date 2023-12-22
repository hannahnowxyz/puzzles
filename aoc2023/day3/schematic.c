//https://adventofcode.com/2023/day/3

#include <stdio.h>

int main()
{
    //load input file into memory
    FILE* stream = fopen("input.txt", "rb");
    fseek(stream, 0, SEEK_END);
    long size = ftell(stream);
    rewind(stream);
    unsigned char* input = (unsigned char*)malloc(size);
    fread(input, 1, size, stream);
    fclose(stream);

    //parse input:
    int next_byte_index = 0;
    unsigned char current_byte = input[next_byte_index++];
    //create edge-padded 2D array and reduce complexity:
    //seek to newline
    while (current_byte != '\n') current_byte = input[next_byte_index++];
    int padded_height = size/next_byte_index + 2;
    int padded_width = next_byte_index + 1;
    //allocate memory for padded array
    unsigned char** schematic_2d = (unsigned char**)malloc(padded_height*sizeof(unsigned char*));
    for (int i = 0; i < padded_height; i++) schematic_2d[i] = (unsigned char*)malloc(padded_width);
    for (int i = 0; i < padded_height; i++) for (int j = 0; j < padded_width; j++) schematic_2d[i][j] = 0;
    //copy and change all "symbols" to '/'
    //note lowest "symbol" found '#' and highest '@', so using 0x23 offset
    const unsigned char ASCIIS[30] = "///////////./0123456789///////";
    for (int j = 0; j < padded_width; j++) schematic_2d[0][j] = '.';
    for (int i = 1; i < padded_height - 1; i++)
    {
        schematic_2d[i][0] = '.';
        for (int j = 1; j < padded_width - 1; j++) schematic_2d[i][j] = ASCIIS[input[(padded_width - 1)*(i - 1) + j - 1] - 0x23];
        schematic_2d[i][padded_width - 1] = '.';
    }
    for (int j = 0; j < padded_width; j++) schematic_2d[padded_height - 1][j] = '.';

    //write to disk (+ newlines) for the lulz
    FILE* outstream = fopen("input2.txt", "wb");
    for (int i = 0; i < padded_height; i++) {fwrite(schematic_2d[i], 1, padded_width, outstream); fputc('\n', outstream);}
    fclose(outstream);
    printf("input preprocessed to input2.txt\n");

    //parse schematic_2d backwards
    int sum = 0;
    for (int i = padded_height - 2; i > 0; i--)
    {
        for (int j = padded_width - 2; j > 0; j--)
        {
            if ('0' <= schematic_2d[i][j] && schematic_2d[i][j] <= '9')
            {
                //parse num back to non-digit and check adjacencies
                int parsed_num[2] = {0};
                int dec_fac = 1;
                char include_in_sum = 0;
                while ('0' <= schematic_2d[i][j] && schematic_2d[i][j] <= '9')
                {
                    parsed_num[1] += dec_fac*(schematic_2d[i][j] - 0x30);
                    dec_fac *= 10;
                    include_in_sum |=
                        schematic_2d[i - 1][j - 1] == '/' || schematic_2d[i - 1][j + 0] == '/' || schematic_2d[i - 1][j + 1] == '/' ||
                        schematic_2d[i + 0][j - 1] == '/' ||                                      schematic_2d[i + 0][j + 1] == '/' ||
                        schematic_2d[i + 1][j - 1] == '/' || schematic_2d[i + 1][j + 0] == '/' || schematic_2d[i + 1][j + 1] == '/';
                    j--;
                }
                
                //add parsed_num to sum if should be included
                sum += parsed_num[include_in_sum];
            }
        }
    }

    //print result
    free(input);
    for (int i = 0; i < padded_height; i++) free(schematic_2d[i]);
    free (schematic_2d);
    printf("sum: %d\n", sum);
    return 0;
}
