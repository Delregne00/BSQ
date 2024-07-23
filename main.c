#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

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
int findMaxSquareSize(char matrix[ROWS][COLS], int startRow, int startCol, char empty) {
    int size = 0;
    // Incrementamos el tamaño mientras sea posible dentro de los límites de la matriz
    while (startRow + size < ROWS && startCol + size < COLS) {
        int i = startRow, j = startCol;
        int valid = 1;  // Asumimos que el cuadrado es válido inicialmente
        // Verificamos si podemos formar un cuadrado de este tamaño
        while (i <= startRow + size && valid) {
            j = startCol;
            while (j <= startCol + size && valid) {
                if (matrix[i][j] != empty) {
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

        printf("%d bytes read!\n", bytesread);
        printf("File Contents: %s\n", buffer);
        printf("what is on the position 11: %c\n ", buffer[13]);

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

        printf("esta es la primera linea: %s\n", arr);
        close(fd);
        return arr;

}
void makesquare(char *rows, char empty, char obstacle, char symbol, char matrix[ROWS][COLS])
{
    int maxSize = 0;
    int maxRow = 0, maxCol = 0;
    int i = 0, j;
    
    printf("em=%c obs=%c sym=%c rows=%s\n", empty, obstacle, symbol, rows);
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (matrix[i][j] == empty) {
            // Si encontramos un espacio vacío, buscamos el cuadrado más grande posible desde esa posición
                int size = findMaxSquareSize(matrix, i, j, empty);
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
            if (matrix[i][j] != empty) {
                matrix[i][j] = obstacle;
                    // Reemplazamos todo con espacios, excepto los obstáculos
            }
            j++;
        }
        i++;
    }
        // Dibujar el cuadrado más grande
    if (maxSize > 0) {
        drawSquare(matrix, maxRow, maxCol, maxSize, symbol);
    }

    // Imprimir el resultado
    printf("Matriz con el cuadrado más grande:\n");
    printMatrix(matrix);
    printf("Tamaño del cuadrado más grande: %d\n", maxSize);
    printf("Posición: (%d, %d)\n", maxRow, maxCol);

    
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
    rows[n] = '\0';  // Asegúrate de terminar la cadena
    empty = str[n];
    obstacle = str[++n];
    symbol = str[++n];
    printf("em=%c obs=%c sym=%c rows=%s\n", empty, obstacle, symbol, rows);

    makesquare(rows, empty, obstacle, symbol, matrix);
    
}
int main(void)
{

        char    *arr = (openfile("map.txt"));

        printf("*arr = %s\n",arr);

    // Inicializamos la matriz con espacios y algunos obstáculos
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



