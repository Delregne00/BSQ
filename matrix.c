#include <stdio.h>

#define ROWS 10
#define COLS 10

void printMatrix(char matrix[ROWS][COLS]) {
    int i = 0, j;
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            printf("%c ", matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void drawSquare(char matrix[ROWS][COLS], int startRow, int startCol, int size, char symbol) {
    int i = startRow;
    while (i < startRow + size) {
        int j = startCol;
        while (j < startCol + size) {
            if (matrix[i][j] == ' ') {
                matrix[i][j] = symbol;
            }
            j++;
        }
        i++;
    }
}

int findMaxSquareSize(char matrix[ROWS][COLS], int startRow, int startCol) {
    int size = 0;
    while (startRow + size < ROWS && startCol + size < COLS) {
        int i = startRow, j = startCol;
        int valid = 1;
        while (i <= startRow + size && valid) {
            j = startCol;
            while (j <= startCol + size && valid) {
                if (matrix[i][j] != ' ') {
                    valid = 0;
                }
                j++;
            }
            i++;
        }
        if (!valid) break;
        size++;
    }
    return size;
}

int main(void) {
    char matrix[ROWS][COLS] = {
        {'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    int squareNumber = 1;
    int i = 0, j;

    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (matrix[i][j] == ' ') {
                int maxSize = findMaxSquareSize(matrix, i, j);
                if (maxSize > 0) {
                    drawSquare(matrix, i, j, maxSize, squareNumber + '0');
                    squareNumber++;
                    if (squareNumber > 9) squareNumber = 1;  // Reset to 1 after 9
                    j += maxSize - 1;  // Move to the last column of the drawn square
                }
            }
            j++;
        }
        i++;
    }

    printf("Matriz con cuadrados numerados:\n");
    printMatrix(matrix);

    return 0;
}