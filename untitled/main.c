#include <stdio.h>
#include <string.h>

#define SIZE1 51
#define SIZE2 101

void enter_array(FILE * i_file, char arr[][SIZE2])
{
    char c = '0';
    int n = 0;
    int m = 0;
    while (!feof(i_file)){
        c = fgetc(i_file);
        if (c != '\n'){
            arr[n][m] = c;
            m++;
        }
        else {
            m = 0;
            n++;
        }
    }

}
int quantity_of_asterisks(char arr[][SIZE2])
{
    int c = 0;
    for (int i = 0; i < SIZE1; i++){
        for (int j = 0; j < SIZE2; j++){
            if (arr[i][j] == '*')
                c++;
        }
    }
    return c;
}
void arr_cpy(char a1[][SIZE2], char a2[][SIZE2])
{
    for (int i = 0; i < SIZE1; i++){
        for (int j = 0; j < SIZE2; j++){
            a2[i][j] = a1[i][j];
        }
    }
}

int simulation(arr)
{
    int cur_x = 1,
        cur_y = 1;

}
int main() {
    FILE* inp = fopen("/home/datsky-prince/CLionProjects/untitled/input.txt", "rt");
    FILE* out = fopen("/home/datsky-prince/CLionProjects/untitled/output.txt", "wt");

    int nAsterisk = 0;
    char grid1[SIZE1][SIZE2] = {0},
         grid2[SIZE1][SIZE2] = {0};

    enter_array(inp, grid1);
    arr_cpy(grid1, grid2);
    nAsterisk = quantity_of_asterisks(grid1);

    /*for (int i = 0 ; i < SIZE1; i++)
    {
        for (int j = 0; j < SIZE2; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    } */
    fclose(inp);
    fclose(out);
}
