//TODO link

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
    //TODO vars

    //until end of file
    while (next_byte_index < size)
    {
        //TODO logic
        current_byte = input[next_byte_index++];
    }
    
    //print result
    free(input);
    printf("result");
    return 0;
}
