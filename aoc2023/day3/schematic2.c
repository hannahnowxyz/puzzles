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
    //copy and remove all "symbols" except '*'
    //note lowest "symbol" found '#' and highest '@', so using 0x23 offset
    const unsigned char ASCIIS[30] = ".......*.....0123456789.......";
    for (int j = 0; j < padded_width; j++) schematic_2d[0][j] = '.';
    for (int i = 1; i < padded_height - 1; i++)
    {
        schematic_2d[i][0] = '.';
        for (int j = 1; j < padded_width - 1; j++) schematic_2d[i][j] = ASCIIS[input[(padded_width - 1)*(i - 1) + j - 1] - 0x23];
        schematic_2d[i][padded_width - 1] = '.';
    }
    for (int j = 0; j < padded_width; j++) schematic_2d[padded_height - 1][j] = '.';
    
    //write to disk (+ newlines) for the lulz
    FILE* outstream = fopen("input3.txt", "wb");
    for (int i = 0; i < padded_height; i++) {fwrite(schematic_2d[i], 1, padded_width, outstream); fputc('\n', outstream);}
    fclose(outstream);
    printf("input preprocessed to input3.txt\n");
    
    //parse schematic_2d backwards: 
    int sum = 0;
    for (int i = padded_height - 2; i > 0; i--)
    {
        for (int j = padded_width - 2; j > 0; j--)
        {
            if (schematic_2d[i][j] == '*')
            {
                //determine if gear:
                //this works by reducing the number of cases.                               offsets:
                //since we always seek-right after,                                         6 5 7
                //if a digit is found at the below-middle or above-middle position,         0 * 1
                //we no longer need to consider the corners of that row.                    3 2 4
                char i_offsets[8] = {0, 0, 1, 1, 1, -1, -1, -1};
                char j_offsets[8] = {-1, 1, 0, -1, 1, 0, -1, 1};
                char numbers_adjacent = 0;
                char number_found_at[8];
                numbers_adjacent += number_found_at[0] = schematic_2d[i + i_offsets[0]][j + j_offsets[0]] >= 0x30;
                numbers_adjacent += number_found_at[1] = schematic_2d[i + i_offsets[1]][j + j_offsets[1]] >= 0x30;
                numbers_adjacent += number_found_at[2] = schematic_2d[i + i_offsets[2]][j + j_offsets[2]] >= 0x30;
                numbers_adjacent += number_found_at[3] = schematic_2d[i + i_offsets[3]][j + j_offsets[3]] >= 0x30 && !number_found_at[2];
                numbers_adjacent += number_found_at[4] = schematic_2d[i + i_offsets[4]][j + j_offsets[4]] >= 0x30 && !number_found_at[2];
                numbers_adjacent += number_found_at[5] = schematic_2d[i + i_offsets[5]][j + j_offsets[5]] >= 0x30;
                numbers_adjacent += number_found_at[6] = schematic_2d[i + i_offsets[6]][j + j_offsets[6]] >= 0x30 && !number_found_at[5];
                numbers_adjacent += number_found_at[7] = schematic_2d[i + i_offsets[7]][j + j_offsets[7]] >= 0x30 && !number_found_at[5];
                if (numbers_adjacent != 2) continue;
                
                //parse gear numbers:
                //get number positions from array
                int k = 0;
                while (!number_found_at[k]) k++;
                int num1_pos[2] = {i + i_offsets[k], j + j_offsets[k++]};
                while (!number_found_at[k]) k++;
                int num2_pos[2] = {i + i_offsets[k], j + j_offsets[k]};

                //seek to end of digits and parse back
                int num1 = 0;
                int num2 = 0;
                while (schematic_2d[num1_pos[0]][num1_pos[1] + 1] >= 0x30) num1_pos[1]++;
                while (schematic_2d[num2_pos[0]][num2_pos[1] + 1] >= 0x30) num2_pos[1]++;
                int dec_fac = 1;
                while (schematic_2d[num1_pos[0]][num1_pos[1]] >= 0x30) {num1 += dec_fac*(schematic_2d[num1_pos[0]][num1_pos[1]--] - 0x30); dec_fac *= 10;}
                dec_fac = 1;
                while (schematic_2d[num2_pos[0]][num2_pos[1]] >= 0x30) {num2 += dec_fac*(schematic_2d[num2_pos[0]][num2_pos[1]--] - 0x30); dec_fac *= 10;}

                //add product to sum
                sum += num1*num2;
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
