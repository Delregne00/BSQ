#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define ROWS 10 
#define COLS 10  

void printMatrix(char matrix[ROWS][COLS]) 
{
    int i;
    int j;

    i = 0; 
    j = 0;
   
    while (i < ROWS) 
    {
        j = 0;
      
        while (j < COLS) 
        {
            printf("%c ", matrix[i][j]);  
            j++;
        }
        printf("\n");  
        i++;
    }
}

int findMaxSquareSize(char matrix[ROWS][COLS], int startRow, int startCol, char empty) 
{
    int size = 0;
    int valid;
    int i;
    int j;

    while (startRow + size < ROWS && startCol + size < COLS)
    {
        i = startRow;
        valid = 1; 
        while (i <= startRow + size && valid) 
        {
            j = startCol;
            while (j <= startCol + size && valid) 
            {
                if (matrix[i][j] != empty) 
                    valid = 0;  
                j++;
            }
            i++;
        }
        if (!valid) break;    
        size++; 
    }
    return size;     
}

void drawSquare(char matrix[ROWS][COLS], int startRow, int startCol, int size, char symbol) 
{
    int i;
    int j;

    i = startRow;
    while (i < startRow + size)
    {
        j = startCol;
        while (j < startCol + size) 
        {
            matrix[i][j] = symbol;  
            j++;
        }
        i++;
    }
}

char *openfile(char *filename)
{
    int fd = open(filename, O_RDWR);
    if(fd == -1)
    {
        write(2, "error opening file\n", 21);
        exit(1);
    }
    write(1, "open successfully!\n", 19);
    char buffer[1024];
    int bytesread = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesread == -1)
    {
        write(2, "error reading file\n", 20);
        close(fd);
        exit(1);
    }
    buffer[bytesread] = '\0';
    char *arr = malloc(bytesread + 1);
    if (arr == NULL)
    {
        write(2, "error allocating memory\n", 25);
        close(fd);
        exit(1);
    }

    int i = 0;
    while (buffer[i] != '\n' && buffer[i] != '\0')
    {
        arr[i] = buffer[i];
        i++;
    }
    arr[i] = '\0';
    close(fd);
    return arr;
}

void findMaxSquare(char matrix[ROWS][COLS], char empty, int *maxSize, int *maxRow, int *maxCol)
{
    int i = 0;
    *maxSize = 0;
    *maxCol = 0;
    *maxRow = 0;
    while (i < ROWS) 
    {
        int j = 0;
        while (j < COLS)
        {
            if (matrix[i][j] == empty)
            {
                int size = findMaxSquareSize(matrix, i, j, empty);
                if (size > *maxSize)
                {
                    *maxSize = size;
                    *maxRow = i;
                    *maxCol = j;
                }
            }
            j++;
        }
        i++;
    }      
}

void setObstacles(char matrix[ROWS][COLS], char empty, char obstacle)
{
    int i = 0;
    while (i < ROWS) 
    {
        int j = 0;
        while (j < COLS) 
        {
            if (matrix[i][j] != empty) 
                matrix[i][j] = obstacle;
            j++;
        }
        i++;
    }
}

void makesquare(char *rows, char empty, char obstacle, char symbol, char matrix[ROWS][COLS])
{
    int maxSize, maxRow, maxCol;
    
    findMaxSquare(matrix, empty, &maxSize, &maxRow, &maxCol);
    setObstacles(matrix, empty, obstacle);
      
    if (maxSize > 0) 
    {
        drawSquare(matrix, maxRow, maxCol, maxSize, symbol);
    }
    printMatrix(matrix);   
}

void values(char *str, char matrix[ROWS][COLS])
{
    char empty;
    char obstacle;
    char symbol;
    char rows[10];
    int n;
    
    n = 0;
    while (str[n] >= '0' && str[n] <= '9')
    {
        rows[n] = str[n];
        n++;
    }
    rows[n] = '\0';  
    empty = str[n];
    obstacle = str[++n];
    symbol = str[++n];
    makesquare(rows, empty, obstacle, symbol, matrix);
}

int main(void)
{
    char *arr = (openfile("map.txt"));
    char matrix[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'o', ' ', ' ', ' ', ' ', 'o', 'o', 'o', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'o', 'o', 'o', ' ', ' ', ' ', ' ', 'o', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    values(arr, matrix);
    return 0;
}