//https://adventofcode.com/2023/day/2

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

    //parse input backwards
    int next_byte_index = size - 1;
    unsigned char current_byte = input[next_byte_index--];
    int sum = 0;

    //until start of file
    while (next_byte_index > 0)
    {
        //proven number of red, green, blue cubes in ascii-betical order
        int min_blue_green_red[19] = {0};

        //line by line
        while (current_byte != ':')
        {
            //seek back to digit and parse num back to space
            while (!('0' <= current_byte && current_byte <= '9')) current_byte = input[next_byte_index--];
            int parsed_num = 0;
            int dec_fac = 1;
            int digits_parsed = 0;
            while (current_byte != ' ')
            {
                parsed_num += dec_fac*(current_byte - 0x30);
                dec_fac *= 10;
                digits_parsed++;
                current_byte = input[next_byte_index--];
            }

            //proven = max(proven, parsed)
            int index = input[next_byte_index + digits_parsed + 3] - 0x62;
            min_blue_green_red[index + 2] = parsed_num - min_blue_green_red[index];
            min_blue_green_red[index] += min_blue_green_red[index + 1 + (min_blue_green_red[index + 2] > 0)];
            current_byte = input[next_byte_index--];
        }

        //add "power" of proven cubes
        sum += min_blue_green_red[0]*min_blue_green_red[5]*min_blue_green_red[16];

        //seek back to newline
        while (current_byte != '\n') current_byte = input[next_byte_index--];
        current_byte = input[next_byte_index--];
    }
    
    //print result
    free(input);
    printf("sum: %d\n", sum);
    return 0;
}
