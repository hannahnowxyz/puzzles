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

    //part 2 preprocessing
    int next_byte_index = 0;
    unsigned char current_byte = input[next_byte_index++];
    const unsigned char ASCIIS[45] = "one  two  threefour five six  seveneightnine ";
    int i = 0;
    int j = 0;

    //until end of file
    while (next_byte_index < size)
    {
        //skip newlines and digits
        while (current_byte > '9')
        {
            i = j = 0;

            //check for substring:
            while (i < 9 && !(
                current_byte == ASCIIS[5*i + j++] &&
                input[next_byte_index] == ASCIIS[5*i + j++] &&
                input[next_byte_index + 1] == ASCIIS[5*i + j++] &&
                (ASCIIS[5*i + j] == ' ' || input[next_byte_index + 2] == ASCIIS[5*i + j++]) &&
                (ASCIIS[5*i + j] == ' ' || input[next_byte_index + 3] == ASCIIS[5*i + j])))
            {i++; j = 0;}

            //set next char to i + ascii offset, loop exits such that i has correct value:
            //"one" becomes "1ne", "five" becomes "5ive", etc
            //if no substring, set char to ':'
            //therefore, "one" eventually becomes "1::" etc
            input[next_byte_index - 1] = i + 0x31;
            current_byte = input[next_byte_index++];
        }

        current_byte = input[next_byte_index++];
    }

    //write to disk
    FILE* outstream = fopen("input2.txt", "wb");
    fwrite(input, 1, size, outstream);
    fclose(outstream);
    free(input);
    printf("input preprocessed to input2.txt\n");
    return part1();
}

//copy-paste
int part1()
{
    //load input file into memory
    FILE* stream = fopen("input2.txt", "rb");
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
