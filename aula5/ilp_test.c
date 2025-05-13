#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

void initialize(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i % 10;
    }
}

long long sum_sequential(int *arr, int size) {
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

long long sum_unrolled(int *arr, int size) {
    long long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    for (int i = 0; i < size; i += 4) {
        sum1 += arr[i];
        sum2 += arr[i+1];
        sum3 += arr[i+2];
        sum4 += arr[i+3];
    }
    return sum1 + sum2 + sum3 + sum4;
}

double measure_time(long long (*func)(int*, int), int *arr, int size) {
    clock_t start = clock();
    long long result = func(arr, size);  // Executa a função e armazena o resultado
    clock_t end = clock();
    printf("Resultado: %lld\n", result);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("Tempo de execução:\n");
    clock_t start = clock();
    initialize(arr, N);
    clock_t end = clock();
    printf("Inicialização: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("Soma sequencial: %.6f s\n", measure_time(sum_sequential, arr, N));
    printf("Soma desenrolada: %.6f s\n", measure_time(sum_unrolled, arr, N));

    free(arr);
    return 0;
}