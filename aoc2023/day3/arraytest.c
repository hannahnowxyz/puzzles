#include <stdio.h>

int main()
{
    int rows = 10;
    int cols = 15;
    //forgot sizeof(unsigned char*) and unironically got braindestroyed for an hour
    unsigned char** bytes_2d = (unsigned char**)malloc(rows*sizeof(unsigned char*));
    for (int i = 0; i < rows; i++) bytes_2d[i] = (unsigned char*)malloc(cols);
    for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) bytes_2d[i][j] = 0;
    return 0;
}
