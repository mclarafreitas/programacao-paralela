#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define N 100000000  // Número de elementos do vetor

// Função para somar elementos de um vetor (Memória-bound) com carga aumentada
void memory_bound(double *arr) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        // Mais operações por elemento, sem tirar o foco em memória
        double val = arr[i] + arr[i] * 0.5 - arr[i] * 0.25 + arr[i] * 0.125;
        sum += val;
    }
}

// Função para calcular operações matemáticas intensivas (Compute-bound) com carga aumentada
void compute_bound() {
    double result = 0.0;
    int n_ops = 500000000;  // Mais operações para sobrecarregar a CPU

    #pragma omp parallel for reduction(+:result)
    for (int i = 1; i < n_ops; i++) {
        double x = i * 0.000001;
        result += sin(x) * cos(x) + log(x + 1.0) * sqrt(x + 2.0) + exp(-x) * tanh(x);
    }

    printf("Resultado final (compute-bound): %f\n", result);
}

int main() {
    // Aloca memória para o vetor
    double *arr = (double *)malloc(N * sizeof(double));
    if (arr == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    // Inicializa o vetor
    for (int i = 0; i < N; i++) {
        arr[i] = 1.0;  // Valores de 1.0 para simplificação
    }

    // Variáveis de tempo
    struct timespec start, end;
    double elapsed_time;

    // Teste de memória-bound
    clock_gettime(CLOCK_MONOTONIC, &start);
    memory_bound(arr);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1.0e9;
    printf("Memória-bound (threads=%d): %f s\n", omp_get_max_threads(), elapsed_time);

    // Teste de compute-bound
    clock_gettime(CLOCK_MONOTONIC, &start);
    compute_bound();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1.0e9;
    printf("Compute-bound (threads=%d): %f s\n", omp_get_max_threads(), elapsed_time);

    // Libera a memória alocada
    free(arr);

    return 0;
}
