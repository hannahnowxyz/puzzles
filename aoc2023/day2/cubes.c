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
    //number of red, green, blue cubes in ascii-betical order
    const int BLUE_GREEN_RED[17] = {14, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12};
    int sum = 0;
    int game_id[2] = {100, 0};

    //until start of file
    while (next_byte_index > 0)
    {
        //possible until proven otherwise
        char impossible = 0;

        //line by line
        while (current_byte != ':')
        {
            //seek back to digit
            while (!('0' <= current_byte && current_byte <= '9')) current_byte = input[next_byte_index--];
            int parsed_num = 0;
            int dec_fac = 1;
            int digits_parsed = 0;
            
            //parse num back to space
            while (current_byte != ' ')
            {
                parsed_num += dec_fac*(current_byte - 0x30);
                dec_fac *= 10;
                digits_parsed++;
                current_byte = input[next_byte_index--];
            }
            
            //check if current game proven impossible
            if (impossible |= parsed_num > BLUE_GREEN_RED[input[next_byte_index + digits_parsed + 3] - 0x62])
            {
                //seek back to colon
                while (current_byte != ':') current_byte = input[next_byte_index--];
                break;
            }
            
            current_byte = input[next_byte_index--];
        }
        
        //add 0 if impossible, else game id
        sum += game_id[impossible];
        game_id[0]--;
        
        //seek back to newline
        while (current_byte != '\n') current_byte = input[next_byte_index--];
        current_byte = input[next_byte_index--];
    }
    
    //print result
    free(input);
    printf("sum: %d\n", sum);
    return 0;
}
