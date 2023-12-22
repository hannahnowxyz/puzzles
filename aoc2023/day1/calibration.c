//https://adventofcode.com/2023/day/1

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

    //parse input
    int next_byte_index = 0;
    unsigned char current_byte = input[next_byte_index++];
    int sum = 0;
    int bytes_read = 0;
    int assignment_index = 0;

    //until end of file
    while (next_byte_index < size)
    {
        assignment_index = 0;
        
        //line by line
        while (current_byte > '\n')
        {
            //set first char to first digit, second to second, etc
            input[bytes_read + assignment_index] = current_byte;
            assignment_index += '0' <= current_byte && current_byte <= '9';
            current_byte = input[next_byte_index++];
        }

        //add to sum
        sum += 10*(input[bytes_read] - 0x30) + input[bytes_read + assignment_index - 1] - 0x30;
        bytes_read += next_byte_index - bytes_read;
        current_byte = input[next_byte_index++];
    }

    //print result
    free(input);
    printf("sum: %d\n", sum);
    return 0;
}
