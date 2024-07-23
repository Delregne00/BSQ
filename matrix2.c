#include <stdio.h>

#define ROWS 10  // Definimos el número de filas de la matriz
#define COLS 10  // Definimos el número de columnas de la matriz

// Función para imprimir la matriz
void printMatrix(char matrix[ROWS][COLS]) {
    int i = 0, j;
    // Recorremos cada fila de la matriz
    while (i < ROWS) {
        j = 0;
        // Recorremos cada columna de la fila actual
        while (j < COLS) {
            printf("%c ", matrix[i][j]);  // Imprimimos el carácter en la posición actual
            j++;
        }
        printf("\n");  // Al final de cada fila, imprimimos un salto de línea
        i++;
    }
}

// Función para encontrar el tamaño máximo de un cuadrado desde una posición dada
int findMaxSquareSize(char matrix[ROWS][COLS], int startRow, int startCol) {
    int size = 0;
    // Incrementamos el tamaño mientras sea posible dentro de los límites de la matriz
    while (startRow + size < ROWS && startCol + size < COLS) {
        int i = startRow, j = startCol;
        int valid = 1;  // Asumimos que el cuadrado es válido inicialmente
        // Verificamos si podemos formar un cuadrado de este tamaño
        while (i <= startRow + size && valid) {
            j = startCol;
            while (j <= startCol + size && valid) {
                if (matrix[i][j] != ' ') {
                    valid = 0;  // Si encontramos un obstáculo, el cuadrado no es válido
                }
                j++;
            }
            i++;
        }
        if (!valid) break;  // Si no es válido, salimos del bucle
        size++;  // Si es válido, incrementamos el tamaño para el próximo intento
    }
    return size;  // Devolvemos el tamaño máximo encontrado
}

// Función para dibujar un cuadrado en la matriz
void drawSquare(char matrix[ROWS][COLS], int startRow, int startCol, int size, char symbol) {
    int i = startRow;
    // Recorremos las filas del cuadrado
    while (i < startRow + size) {
        int j = startCol;
        // Recorremos las columnas del cuadrado
        while (j < startCol + size) {
            matrix[i][j] = symbol;  // Dibujamos el símbolo en cada posición del cuadrado
            j++;
        }
        i++;
    }
}

int main(void) {
    // Inicializamos la matriz con espacios y algunos obstáculos
    char matrix[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', 'o', 'o', 'o', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'o', 'o', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'o', 'o', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'o', 'o', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'o', 'o', 'o', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    int maxSize = 0;  // Tamaño del cuadrado más grande encontrado
    int maxRow = 0, maxCol = 0;  // Posición del cuadrado más grande
    int i = 0, j;

    // Encontrar el cuadrado más grande
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (matrix[i][j] == ' ') {
                // Si encontramos un espacio vacío, buscamos el cuadrado más grande posible desde esa posición
                int size = findMaxSquareSize(matrix, i, j);
                if (size > maxSize) {
                    // Si encontramos un cuadrado más grande, actualizamos los valores máximos
                    maxSize = size;
                    maxRow = i;
                    maxCol = j;
                }
            }
            j++;
        }
        i++;
    }
    
    // Limpiar la matriz (excepto los obstáculos)
    i = 0;
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (matrix[i][j] != 'o') {
                matrix[i][j] = ' ';  // Reemplazamos todo con espacios, excepto los obstáculos
            }
            j++;
        }
        i++;
    }

    // Dibujar el cuadrado más grande
    if (maxSize > 0) {
        drawSquare(matrix, maxRow, maxCol, maxSize, '#');
    }

    // Imprimir el resultado
    printf("Matriz con el cuadrado más grande:\n");
    printMatrix(matrix);
    printf("Tamaño del cuadrado más grande: %d\n", maxSize);
    printf("Posición: (%d, %d)\n", maxRow, maxCol);

    return 0;
}