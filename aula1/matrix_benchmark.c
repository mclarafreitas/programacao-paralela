#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 100
#define MAX_SIZE 4000
#define STEP_SIZE 200

double matrix[MAX_SIZE][MAX_SIZE];
double vector[MAX_SIZE], result[MAX_SIZE];

void fill_data(int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 10;
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void row_major(int size) {
    for (int i = 0; i < size; i++) {
        result[i] = 0;
        for (int j = 0; j < size; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void col_major(int size) {
    for (int i = 0; i < size; i++) result[i] = 0;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

double measure_time(void (*func)(int), int size) {
    clock_t start = clock();
    func(size);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    printf("Size\tRow-Major (s)\tCol-Major (s)\n");
    
    for (int size = MIN_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        fill_data(size);
        double time_row = measure_time(row_major, size);
        double time_col = measure_time(col_major, size);
        printf("%d\t%.6f\t%.6f\n", size, time_row, time_col);
    }
    return 0;
}
