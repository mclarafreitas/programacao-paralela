#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 100
#define MAX_SIZE 4000
#define STEP_SIZE 200

// Função para alocar matriz dinamicamente
double** allocate_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Função para liberar matriz
void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Multiplicação por linhas (linha externa, coluna interna)
void matrix_vector_row_major(double** matrix, double* vector, double* result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

// Multiplicação por colunas (coluna externa, linha interna)
void matrix_vector_col_major(double** matrix, double* vector, double* result, int rows, int cols) {
    for (int i = 0; i < rows; i++) result[i] = 0.0; // Inicializa o vetor resultado

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

// Medição de tempo de execução
double measure_time(void (*func)(double**, double*, double*, int, int), double** matrix, double* vector, double* result, int rows, int cols) {
    clock_t start, end;
    start = clock();
    func(matrix, vector, result, rows, cols);
    end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));

    printf("Size\tRow-Major (s)\tCol-Major (s)\n");

    for (int size = MIN_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        // Aloca matriz e vetor
        double** matrix = allocate_matrix(size, size);
        double* vector = (double*)malloc(size * sizeof(double));
        double* result = (double*)malloc(size * sizeof(double));

        // Inicializa matriz e vetor com valores aleatórios
        for (int i = 0; i < size; i++) {
            vector[i] = (double)(rand() % 10);
            for (int j = 0; j < size; j++) {
                matrix[i][j] = (double)(rand() % 10);
            }
        }

        // Mede os tempos de execução
        double time_row = measure_time(matrix_vector_row_major, matrix, vector, result, size, size);
        double time_col = measure_time(matrix_vector_col_major, matrix, vector, result, size, size);

        // Exibe os tempos
        printf("%d\t%.6f\t%.6f\n", size, time_row, time_col);

        // Libera memória
        free_matrix(matrix, size);
        free(vector);
        free(result);
    }

    return 0;
}
