#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000  // Tamanho do vetor

void initialize_vector(float *arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = (i % 100) * 0.5f;  // Cálculo simples para inicialização
    }
}

float sum_accumulative(float *arr) {
    float sum = 0.0f;
    for (int i = 0; i < N; i++) {
        sum += arr[i];  // Dependência entre iterações
    }
    return sum;
}

float sum_reduction(float *arr) {
    float sum1 = 0.0f, sum2 = 0.0f, sum3 = 0.0f, sum4 = 0.0f;
    for (int i = 0; i < N; i += 4) {
        sum1 += arr[i];
        sum2 += arr[i + 1];
        sum3 += arr[i + 2];
        sum4 += arr[i + 3];
    }
    return sum1 + sum2 + sum3 + sum4;  // Reduzindo a dependência
}

void benchmark(float (*func)(float *), float *arr, const char *label) {
    clock_t start = clock();
    float result = func(arr);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s: Resultado = %f, Tempo = %.6f segundos\n", label, result, time_spent);
}

int main() {
    float *arr = (float *)malloc(N * sizeof(float));
    if (!arr) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    initialize_vector(arr);
    
    benchmark(sum_accumulative, arr, "Soma Acumulativa");
    benchmark(sum_reduction, arr, "Soma com Quebra de Dependência");
    
    free(arr);
    return 0;
}
